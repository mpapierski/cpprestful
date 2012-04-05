#if !defined(CPPRESTFUL_H)
#define CPPRESTFUL_H

#include <exception>
#include <string>
#include <map>
#include <list>

#include <curl/curl.h>

/* cpprestful namespace */
namespace cpprestful {
	
/* cpprestful exceptions */
namespace exceptions {

/**
 * Unable to initialize client class.
 */
struct init_failure: std::exception
{
	init_failure() throw() {}
	~init_failure() throw() {}
	
	virtual const char* what() throw()
	{
		return "Unable to initialize client class instance.";
	}
};

/**
 * Thrown when trying to make queries using store, when the underlying store
 * is not bound to a client.
 */
struct store_unbound: std::exception
{
	store_unbound() throw() {}
	~store_unbound() throw() {}
	virtual const char* what() throw()
	{
		return "Store is not bound to a client proxy.";
	}
};

/**
 * Thrown when trying to make queries using store, when the underlying store
 * is not bound to a client.
 */
struct query_error: std::exception
{
	query_error() throw() {}
	~query_error() throw() {}
	virtual const char* what() throw()
	{
		return "HTTP query returns an error.";
	}
};


/* /exceptions */
}

/**
 * Basic interface to the CURL library.
 */
class client
{
private:
	/**
	 * CURL handle
	 */
	CURL* m_CURL;
	
public:
	/**
	 * Default constructor
	 */
	client();
		
	/**
	 * Destroy CURL handle.
     */		
	~client();
	
	/**
	 * Perform a GET query.
	 * @param address URL address.
     */
	void GET(const std::string& address);
};

/**
 * API provides an interface to a HTTP(S) service.
 */
class api
{
private:
	/**
	 * Base URL address for the API.
	 */
	std::string m_URL;
	
public:
	/**
	 * Create new API using provided base URL.
	 * 
	 * Valid URL addresses:
	 * http://localhost/api/v1
	 * 
	 * @param url URL address.
	 */
	api(const std::string& url);
	
	/**
	 * Get the base URL address for RESTful API.
     * @return Base URL.
     */
	inline const std::string& url() const
	{
		return m_URL;
	}
};

/**
 * Concept and an base interface of a "Model".
 * 
 * Class implements a Model concept if:
 * Subclasses cpprestful::model class.
 * Contains static method named "model_name" which returns model name.
 */
class model
{
private:
public:
	model();
	~model();
};

/**
 * Store class is a bridge between client, reader, api, and the model.
 */
template <typename Model>
class store
{
private:
	/**
	 * Client instance.
	 * 
	 * Using default constructor the store is not yet configured, and so it is
	 * unable to make queries.
	 */
	client* m_Client;
	
	/**
	 * API instance. Now store knows where queries can be made.
	 */
	api* m_Api;
	
public:
	store() :
		m_Client(0),
		m_Api(0) {}
		
	~store() {}
	
	/**
	 * Query for a complete list of clients.
	 * 
	 * 1.
	 * 
	 * @return Model list.
	 */
	std::list<Model> records()
	{
		if (!m_Client)
			throw exceptions::store_unbound();
		if (!m_Api)
			throw exceptions::store_unbound();
		
		std::string address = m_Api->url() + Model::name();
		m_Client->GET(address);
		return std::list<Model>();
	}
	
	/**
	 * Set a client.
	 * Never throws.
	 * @param client_proxy New client proxy
	 */
	void bind(client* client_proxy, api* restful_api) throw()
	{
		m_Client = client_proxy;
		m_Api = restful_api;
	}
};

/* /cpprestful */
}

#endif