// -*- C++ -*-

#ifndef OBJ_REPOSITORY_H_
#define OBJ_REPOSITORY_H_


/**
 * @class obj_repository
 * 
 * @brief
 */
template<typename OBJ, bool hash = true>
class obj_repository
{ };
template<typename OBJ>
class obj_repository<OBJ, false>
{
public:
  obj_repository(int size)
    :size_(size),
    obj_items_(NULL)
  { 
    obj_items_ = new OBJ*[size_]; 
    for (int i = 0; i < size_; ++i)
      obj_items_[i] = NULL;
  }

  ~obj_repository()
  {
    if (this->obj_items_)
      delete []this->obj_items_;
    this->obj_items_ = 0;
  }

  inline int bind(int obj_id, OBJ *si)
  {
    if (this->is_valid_id(obj_id))
    {
      this->obj_items_[obj_id] = si;
      return 0;
    }
    return -1;
  }

  inline bool is_valid_id(int id)
  { return id < this->size_ && id >= 0; }

  inline OBJ *find(int obj_id)
  { 
    if (this->is_valid_id(obj_id))
      return this->obj_items_[obj_id];
    return NULL;
  }
private:
  int size_; 

  OBJ **obj_items_;
};
template<typename OBJ>
class obj_repository<OBJ, true>
{
public:
  obj_repository(int size)
    :size_(size)
  { }

  ~obj_repository()
  { }

  inline int bind(int obj_id, OBJ *si)
  {
    if (this->is_valid_id(obj_id))
    {
      std::pair<obj_items_iter, bool> ret = 
        this->obj_items_.insert(std::make_pair(obj_id,
                                               si));
      return ret.second ? 0 : -1;
    }
    return -1;
  }

  inline bool is_valid_id(int id)
  { return id < this->size_ && id >= 0; }

  inline OBJ *find(int obj_id)
  { 
    if (this->is_valid_id(obj_id))
    {
      obj_items_iter ret = this->obj_items_.find(obj_id);
      if (ret == this->obj_items_.end())
        return NULL;
      return ret->second;
    }
    return NULL;
  }
private:
  int size_;

  typedef typename boost::unordered_map<int, OBJ *> obj_items_t;
  typedef typename boost::unordered_map<int, OBJ *>::iterator obj_items_iter;
  obj_items_t obj_items_;
};

#endif // OBJ_REPOSITORY_H_

