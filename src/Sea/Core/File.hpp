#pragma once

#include <string>

namespace Sea
{ 
	class File
	{
	public:
		static std::string AssetsFolder;

	public:
		static const std::string GetFileContent(File file);
		static const std::string GetFileContent(const std::string_view filepath, bool _internal = true);

		bool Exist() const ;
		const std::string& Read();
		const std::string& GetContent() const;
		const std::string& GetPath() const;
		const std::string& GetExtenstion() const;

		File(const std::string_view filepath, bool _internal = true);
		File(const File&) = default;
		File(File&&) = default;
		~File() = default;

	private:
		std::string m_content;
		std::string m_filepath;
		std::string m_ext;
	};
}