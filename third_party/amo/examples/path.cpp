#include <iostream>

#include <amo/path.hpp>

int main(int argc, char** argv)
{
	const LPCSTR MUSIC_FILE_EXT_NAME[] =
	{ ".mp3", ".wma", ".aac", ".ogg", ".wav", ".m4a", ".amr", ".ape", ".cue", ".flac", ".mkv" };
	amo::path path("D:/a.txt -d 23 -c 32");
	amo::path p1("D:");
	amo::path p2("video/");
	p1.combine(p2);
	p1.skip_root();
	p1.strip_path();
	path.remove_args();
	amo::path p3("C:\\Users\\Default\\AppData\\Local\\Microsoft\\Windows\\History");
	amo::path p4("\\Windows\\History");
	p3.unexpand_env_strings();
	p3.find_on_path(p4);
	amo::string ssb = p3.find_next_component();
	ssb = p3.find_next_component();
	amo::path p5("D:/video/oh.mkv");
	bool bOk = p3.find_suffix_array((const char**)MUSIC_FILE_EXT_NAME, 11);
	bool bOk1 = p5.find_suffix_array((const char**)MUSIC_FILE_EXT_NAME, 11);

	amo::path p6("D:\\a\\b");
	amo::path p7("D:\\a\\c");
	p6.relative_path_to(p7);
	amo::path p8("A:\\name_1\\.\\name_2\\..\\name_3");
	p8.canonicalize();
	amo::path p9("C:\\Users\\Default\\AppData\\Local\\Microsoft\\Windows\\History\\ / : * ? \" < > | ");
	p9.cleanup_spec();
	p9.get_short_path_name();

 

	amo::path p10("D:\\cef-Out");
	amo::path p11("E:\\cef2-Out");

	int i = 0;
	std::vector<amo::string> oSet;
	oSet.push_back(".obj");
	oSet.push_back(".pch");
	oSet.push_back(".pdb");
	oSet.push_back(".cc");
	p10.transfer([&](amo::path& p){ 
		if (p.find_suffix_array(oSet)) return;
		++i;
		amo::path p1 = p.relative_path_to_c(p10);
		amo::path p2 = p11.append_c(p1);
		bool bOk = p.copy_to(p2);
	}, true);
	std::cout << i << std::endl;
	return 0;
}