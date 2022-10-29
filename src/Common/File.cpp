#include "Sea/Common/File.hpp"

#include <fstream>

namespace Sea
{
	std::string File::FROM_SOURCE = "../../";

	const std::string File::GetFileContent(File file)
	{
		file.Read();
		return file.GetContent();
	}

	const std::string File::GetFileContent(const std::string filepath)
	{
		return GetFileContent(File(filepath));
	}

	const std::string File::Read()
	{
		std::ifstream ifs(m_filepath);
		std::string content((std::istreambuf_iterator<char>(ifs)),
			(std::istreambuf_iterator<char>()));
		m_content = std::string(content.c_str());
		return m_content;
	}

	const std::string File::GetContent()
	{
		return std::string(m_content);
	}

	const std::string File::GetPath()
	{
		return m_filepath;
	}

	File::File(const std::string filepath) :
		m_filepath(FROM_SOURCE+filepath)
	{

	}
}
