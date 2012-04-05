#include <cpprestful.hpp>
#include <curl/curl.h>

using namespace cpprestful;

client::client() :
	m_CURL(curl_easy_init())
{
	if (!m_CURL)
		throw exceptions::init_failure();
}

client::~client()
{
	curl_easy_cleanup(m_CURL);
}

void client::GET(const std::string& address)
{
	// Set the URL
	curl_easy_setopt(m_CURL, CURLOPT_URL, address.c_str());
	
	// Get result
	CURLcode result = curl_easy_perform(m_CURL);
	
	if (!result)
	{
		throw exceptions::query_error();
	}
}

api::api(const std::string& url) :
	m_URL(url)
{
	
}

model::model()
{
	
}

model::~model()
{
	
}