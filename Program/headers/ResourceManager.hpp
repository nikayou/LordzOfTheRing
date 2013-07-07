#include <map>
#include <string>

template <typename T>
class ResourceManager
{
protected:
  ResourceManager () { }
  ~ResourceManager () { }
 std::map<std::string, T > mData;
  /**
     Add an element to data
   */
  virtual void add(const std::string& s, const T& t){
    std::string n = s;
    mData.insert( std::pair<std::string, T>(n, t) );
  }
  /**
     Remove an element from data, given its name (key)
   */
  virtual void remove(const std::string& n){
    mData.erase(n);
  }
  /**
     load a data from a file and adds it to data
   */
  virtual bool loadFromFile(const std::string& path){
    T t;
    if(!t.loadFromFile(path) ){
      return false;
    }
    add(path, t);
    return true;
  }

public:
  /**
     Tries to return the value matching the key.
     If not here, tries to load it from the file.
     If failure, return NULL, otherwise returns pointer to the value.
   */
  T * get(const std::string& n){
    if(mData.find(n) == mData.end() ){
      if(loadFromFile(n) )
	return &mData[n];
      else
	return NULL;
    }
    return &mData[n];
  }
  // Interface publique
  static ResourceManager *getInstance ()
  {
    if (NULL == _resourceManager)
      {
	//creation singleton
        _resourceManager = new ResourceManager;
      }

    return _resourceManager;
  }

  static void kill ()
  {
    if (NULL != _resourceManager)
      {
        delete _resourceManager;
        _resourceManager = NULL;
      }
  }

private:
  // Unique instance
  static ResourceManager *_resourceManager;
};

template <typename T>
ResourceManager<T> *ResourceManager<T>::_resourceManager = NULL;
