#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <vector>
#include <memory>
#include <functional>
#include <algorithm>
#include <string>
#include <sstream>
#include <boost/algorithm/string.hpp>

template<class T> class Repository
{
        std::vector<std::shared_ptr<T>> objects;
public:
        Repository() = default;
        virtual ~Repository() = default;

        virtual std::string report() const;
        virtual size_t size() const;

        template<class P> std::vector<std::shared_ptr<T>> findBy(const P &predicate) const;
        template<class P> std::shared_ptr<T> findFirst(const P &predicate) const;
        virtual std::vector<std::shared_ptr<T>> findAll() const;
protected:
        virtual std::shared_ptr<T> get(size_t index) const;
        virtual void add(std::shared_ptr<T> object);
        virtual void remove(std::shared_ptr<T> object);
};

template<class T> std::shared_ptr<T> Repository<T>::get(size_t index) const
{
        return (index >= objects.size()) ? nullptr : objects[index];
}

template<class T> void Repository<T>::add(std::shared_ptr<T> object)
{
        if (object) objects.push_back(object);
}

template<class T> void Repository<T>::remove(std::shared_ptr<T> object)
{
        objects.erase(std::remove(objects.begin(), objects.end(), object), objects.end());
}

template<class T> std::string Repository<T>::report() const
{
        std::stringstream ss;
        std::for_each(objects.begin(), objects.end(), [&ss](const std::shared_ptr<T> &o) {
                ss << o->getInfo() << " ";
        });
        return boost::trim_right_copy(ss.str());
}

template<class T> size_t Repository<T>::size() const
{
        return objects.size();
}

template<class T> template<class P> std::vector<std::shared_ptr<T>> Repository<T>::findBy(const P &predicate) const
{
        std::vector<std::shared_ptr<T>> found;
        std::copy_if(objects.begin(), objects.end(), std::back_inserter(found), predicate);
        return found;
}

template<class T> template<class P> std::shared_ptr<T> Repository<T>::findFirst(const P &predicate) const
{
        auto iter = std::find_if(objects.begin(), objects.end(), predicate);
        return (iter != objects.end()) ? *iter : nullptr;
}

template<class T> std::vector<std::shared_ptr<T>> Repository<T>::findAll() const
{
        return findBy([](std::shared_ptr<T> o) { return true; });
}

#endif // REPOSITORY_H
