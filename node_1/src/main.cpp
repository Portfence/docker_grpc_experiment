#include <iostream>
#include <../build/AddressBook.pb.h>

using std::cout;
using std::endl;

int main(int argc, char * argv[])
{  
  GRPC_Experiment::Person p1;
  p1.set_name("Albert");
  p1.set_id(1);
  cout << "First person name and id: " << p1.name() << ", " << p1.id() << endl;

  GRPC_Experiment::AddressBook b;

  return 0;
}
