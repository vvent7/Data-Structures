#ifndef KEY_DATA_CONTAINER_H
#define KEY_DATA_CONTAINER_H

#include<memory> //unique_ptr
#include<vector> //vector<Data>

/* The container assumes that the operation is always successful
 *  - Does not check for duplicates
 *  - Does not check for empty container
 *  - Does not check for non-existing data ( data2locator[x] ) */
template <typename Data, typename DataLocator>
class key_data_container{
public:
  virtual ~key_data_container() = default;

  virtual size_t size() const = 0;
  virtual bool empty() const = 0;
  virtual Data minimum() const = 0;
  virtual Data maximum() const = 0;

  virtual void insert(Data x, std::unique_ptr<DataLocator[]> &data2dataLoc) = 0;

  virtual void remove(Data x, std::unique_ptr<DataLocator[]> &data2dataLoc) = 0;

  virtual Data extract_min(std::unique_ptr<DataLocator[]> &data2dataLoc) = 0;

  virtual std::vector<Data> extract_all() = 0;
};

#endif