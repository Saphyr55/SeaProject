#include <memory>
#include <fstream>
#include <filesystem>

#include <fmt/printf.h>

#include "Sea/Core/File.hpp"

namespace fs = std::filesystem;

namespace Sea
{
	std::string File::AssetsFolder;

	const std::string File::GetFileContent(File file)
	{
		return file.Read();
	}

	const std::string File::GetFileContent(const std::string_view filepath, bool _internal)
	{
		return GetFileContent(File(filepath, _internal));
	}

	bool File::Exist() const
	{
		return fs::exists(fs::path(m_filepath));
	}

	const std::string& File::Read()
	{	
		if (!fs::exists(fs::path(m_filepath)))
		{
			fmt::printf("{} doesn't exist.\n", m_filepath);
			throw std::exception();
		}

		std::ifstream ifs(m_filepath);
		std::string content((std::istreambuf_iterator<char>(ifs)),
			(std::istreambuf_iterator<char>()));
		m_content = std::string(content.c_str());
		return m_content;
	}

	const std::string& File::GetContent() const
	{
		return std::string(m_content);
	}

	const std::string& File::GetPath() const
	{
		return m_filepath;
	}

	const std::string& File::GetExtenstion() const
	{
		return m_ext;
	}

	File::File(const std::string_view filepath, bool _internal) :
		m_ext(fs::path(filepath).extension().string())
	{
		if (_internal) m_filepath = AssetsFolder + filepath.data();
		else m_filepath = filepath;
	}
}
