#pragma once

#include <string>
#include <memory>

namespace Sea
{ 
	class File final
	{
	public:
		static std::string FromResources;

	public:
		static const std::string GetFileContent(File file);
		static const std::string GetFileContent(const std::string_view filepath, bool _internal = true);

		bool Exist();
		const std::string Read();
		const std::string GetContent();
		const std::string GetPath();
		const std::string GetExtenstion();

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