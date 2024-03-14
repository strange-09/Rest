#include<cpprest/http_client.h>
#include<cpprest/filestream.h>
#include<cpprest/json.h>
#include<iostream>
#include<string>
using namespace std;
using namespace web;
using namespace web::http;
using namespace web::http::client;

class Weather {
private:
	string city;
	string api_key;
public:
	Weather(const string& city, const string& api_key) :city(city), api_key(api_key) {}
	void getrestdata() {
		uri_builder builder(U("https://api.openweathermap.org/data/2.5/weather"));
		builder.append_query(U("q"), utility::conversions::to_string_t(city));
		builder.append_query(U("appid"), utility::conversions::to_string_t(api_key));
		builder.append_query(U("units"), U("metric"));

		http_client client(builder.to_string());
		client.request(methods::GET).then([](http_response response) {
			if (response.status_code() >= 200 && response.status_code() < 300) {
				return response.extract_json();
			}
			else {
				throw runtime_error("Failed to get weather data .");
			}
			}).then([](json::value weatherData) {
				cout << "Temperature: " << weatherData.at(U("main")).at(U("temp")).as_double() << "C" << endl;
				//	cout << "Description: " << weatherData.at(U("weather"))[0].at(U("description")).as_string() << endl;
				}).wait();
	}
};
int main() {
	cout << "----------------------------------------" << endl;
	cout << "	     Rest Weather" << endl;
	cout << "----------------------------------------" << endl;

	string city;
	cout << ("Enter City Name to view Weather : ");
	getline(cin, city);

	string API_KEY = "4900eb2e85089d907da0ad428bc9f7a3";

	Weather rest(city, API_KEY);
	rest.getrestdata();

	cout << "Task completed. Press Enter to exit.";
	cin.get();

	return 0;
}