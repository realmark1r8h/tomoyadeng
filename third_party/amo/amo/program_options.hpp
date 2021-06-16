// Created by ËÕÔªº£ on 08/17/2016.
// Copyright (c) 2016 amoylel. All rights reserved.

#ifndef IME_PROGRAM_OPTIONS_HPP__
#define IME_PROGRAM_OPTIONS_HPP__

#include <string>
#include <utility>
#include <fstream>
#include <iostream>
#include <sstream>

#include <amo/config.hpp>
#include <amo/unordered_map.hpp>
#include <amo/functional.hpp>


namespace amo
{  
	namespace po = boost::program_options;

	inline std::pair<std::string, std::string> at_option_parser(std::string const&s)
	{
		if ('@' == s[0])
			return std::make_pair(std::string("config-file"), s.substr(1));
		else
			return std::pair<std::string, std::string>();
	}

	class program_options 
	{
	public:
		program_options() : desc("options")
		{
			 
		}

		~program_options() { }

		po::options_description_easy_init add_options()
		{
			return desc.add_options();
		}

		size_t count(const std::string& key)
		{
			return vm.count(key);
		}

		po::variables_map& variables_map()
		{
			return vm;
		}

		const po::variable_value& operator[](const std::string& name)
		{
			return vm[name];
		}

		virtual bool parse_string_line(const std::string& str)
		{
			try
			{
				vm.clear();
				boost::char_separator<char> sep(" \n\r");
				boost::tokenizer<boost::char_separator<char> > tok(str, sep);
				std::vector<std::string> args;

				std::copy(tok.begin(), tok.end(), back_inserter(args));

				po::store(po::command_line_parser(args).options(desc).run(), vm);
				 
				return on_parse_completed(vm);
			}
			catch (std::exception& e)
			{
				std::cout << e.what() << std::endl;
				return false;
			}
		}

		virtual bool parse_command_line(int argc, char** argv)
		{
			
			try
			{ 
				/*po::store(po::command_line_parser(argc, argv).options(desc)
					.extra_parser(at_option_parser).run(), vm);*/
				po::store(po::parse_command_line(argc, argv, desc), vm);
				if (vm.count("config-file"))
				{
					std::string config_file = vm["config-file"].as<std::string>();

					std::ifstream ifs(config_file.c_str());
					if (!ifs)
					{
						std::cout << "could not open the config file:" << config_file << std::endl;
						return false;
					}

					std::stringstream ss;
					ss << ifs.rdbuf();

					boost::char_separator<char> sep(" \n\r");
					std::string sstr = ss.str();

					boost::tokenizer<boost::char_separator<char> > tok(sstr, sep);
					std::vector<std::string> args;

					std::copy(tok.begin(), tok.end(), back_inserter(args));

					po::store(po::command_line_parser(args).options(desc).run(), vm);
				}
				return on_parse_completed(vm);
			}
			catch (std::exception& e)
			{
				std::cout << "parse failed: " << e.what() << std::endl;
				return false;
			}
		}


		virtual bool on_parse_completed(po::variables_map& vm)
		{
			return true;
		}

		friend std::ostream& operator<<(std::ostream& o, const program_options& parser);
	protected:
		po::options_description desc;
		po::positional_options_description p;
		po::variables_map vm;
	};

	inline std::ostream& operator<<(std::ostream& o, const program_options& parser)
	{
		return o << parser.desc;
	}
}


#endif // IME_PROGRAM_OPTIONS_HPP__
