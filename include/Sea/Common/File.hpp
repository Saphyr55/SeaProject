#pragma once

#include <string>
#include <memory>

namespace Sea
{ 
	class File final
	{
	public:
		static const std::string GetFileContent(File /* file */);
		static const std::string GetFileContent(const std::string /* filepath */);

		const std::string Read();
		const std::string GetContent();

		File(const std::string filepath);
		File(const File&) = default;
		File(File&&) = default;
		~File() = default;

	private:
		std::string m_content;
		const std::string m_filepath;
	};
}