#ifndef RESOURCEMANAGER_HPP
#define RESOURCEMANAGER_HPP

#include <map>
#include <string>

#include <iostream>

template <class T>
class ResourceManager
{


protected:
  std::map<std::string, T > mData;
  ResourceManager () { 
   }
  ~ResourceManager () { 
    mData.clear();
  }
  /**
     Add an element to data
   */
  virtual void add(const std::string& s, const T& t){
    std::cout<<"adding resource \""<<s<<"\""<<std::endl;
    mData.insert( std::pair<std::string, T>(s, t) );
  }



public:  
  /**
     Tries to return the value matching the key.
     If not here, tries to load it from the file.
     If failure, return NULL, otherwise returns pointer to the value.
   */
  virtual T * get(const std::string& n){
    T t;
    std::cout<< "trying to get resource "<<n<<std::endl;
    if(mData.find(n) == mData.end() ){
      std::cout<< "not present"<<std::endl;
      if( t.loadFromFile(n) ){
	std::cout<<"Loaded resource \""<<n<<"\""<<std::endl;
	add(n, t);
	std::cout<<"added \""<<n<<"\" at "<<&mData[n]<<std::endl;
	return &mData[n];
      }else{
	//std::cout<<"Couldn't load resource \""<<n<<"\""<<std::endl;
	return NULL;
      }
    }
    return &mData[n];
  }


   virtual std::string getClass(){ 
    return "ResourceManager"; 
  };

  /**
     Remove an element from data, given its name (key)
   */
  virtual void remove(const std::string& n){
    std::cout<<"Removing resource \""<<n<<"\""<<std::endl;
    if( mData.find(n) == mData.end() )
      mData.erase(n);
  }

  /**
     Remove all elements
   */
  virtual void clear(){
    mData.clear();
  }
  
};

#endif
