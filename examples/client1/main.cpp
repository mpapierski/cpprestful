#include <iostream>
#include <string>
#include <cpprestful.hpp>

using namespace std;

struct person: cpprestful::model
{
	static const char* name()
	{
		return "person";
	}
	
	person()
	{
		
	}
	
	friend
	ostream& operator<< (ostream& out, const person& le_person)
	{
		out << "person()";
		return out;
	}
};

struct api_v1: cpprestful::api
{
	api_v1():
		cpprestful::api("http://localhost:8000/api/v1/")
	{
		
	}
};

typedef cpprestful::store<person> person_store;

int main(int argc, char* argv[])
{
	// le client (proxy)
	cpprestful::client client;
	
	// le restful api
	api_v1 api;
	
	// le reader (not yet...)
	// TODO
	
	// le store
	person_store store;
	
	// store is now using le client (and someday le data reader)
	store.bind(&client, &api);
	
	std::list<person> person_list;
	try
	{
		// le blocking query
		person_list = store.records();
	}
	catch (cpprestful::exceptions::query_error& e)
	{
		cerr << "cpprestful query error: " << e.what() << endl;
		return 1;
	}
		
	
	// le clients
	for (std::list<person>::const_iterator it(person_list.begin()),
		end(person_list.end()); it != end; ++it)
	{
		cout << *it << endl;
	}
	return 0;
}