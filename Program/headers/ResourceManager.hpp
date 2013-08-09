#ifndef RESOURCEMANAGER_HPP
#define RESOURCEMANAGER_HPP

#include <iostream> //delete
#include <map>
#include <string>

template <class T>
class ResourceManager
{
protected:
  std::map<std::string, T > mData;
  ResourceManager () { //std::cout<<"ResourceManager created "<<std::endl; 
}
  ~ResourceManager () { }
  /**
     Add an element to data
   */
  virtual void add(const std::string& s, const T& t){
    std::string n = s;
    //std::cout<< "adding resource "<<s<<std::endl;
    mData.insert( std::pair<std::string, T>(n, t) );
  }
  /**
     Remove an element from data, given its name (key)
   */
  virtual void remove(const std::string& n){
    mData.erase(n);
  }


public:  
  /**
     Tries to return the value matching the key.
     If not here, tries to load it from the file.
     If failure, return NULL, otherwise returns pointer to the value.
   */
  virtual T * get(const std::string& n){
    T t;
    //std::cout<< "trying to get resource "<<n<<"("<<t.getClass()<<")"<<std::endl;
    if(mData.find(n) == mData.end() ){
      //std::cout<< "not present"<<std::endl;
      if( t.loadFromFile(n) ){
	add(n, t);
	return &mData[n];
      }else
	return NULL;
    }
    return &mData[n];
  }

  virtual std::string toString(){
    typename std::map<std::string, T>::iterator it;
    std::string res = "";
    for(it = mData.begin(); it != mData.end(); ++it){
      res += it->first;
      res += " = \n";
      //res += it->second.toString();
      res += "\n";
    }
    return res;
  };
  virtual std::string getClass(){ 
    return "ResourceManager"; 
  };

};

#endif
