//#include <iostream>
//
//#include <amo/json.hpp>
//
//int main(int argc, char** argv)
//{
//	amo::json js_ = amo::json::from_file("D:/config.json");
//	int port = js_.get<int>("port");
//
//	amo::json jso;
//	jso.put(34);
//	bool bOk = jso.is_int64();
//	std::cout << jso.to_string() << std::endl;
//	return 0;
//}