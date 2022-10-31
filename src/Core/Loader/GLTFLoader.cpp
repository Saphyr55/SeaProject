#include <Sea/Core/Loader/GLTFLoader.hpp>

namespace Sea
{
	
	GLTFLoader::GLTFLoader(File file) : AbstractLoader(file)
	{
		std::string content = m_file.Read();
		m_dataJson = json::parse(content);
		m_data = GetData();
		TraverseNode(0);
	}
	
	void GLTFLoader::LoadMesh(u32 indMesh)
	{
		// Get all accessor indices
		u32 posAccInd = m_dataJson["meshes"][indMesh]["primitives"][0]["attributes"]["POSITION"];
		u32 normalAccInd = m_dataJson["meshes"][indMesh]["primitives"][0]["attributes"]["NORMAL"];
		u32 texAccInd = m_dataJson["meshes"][indMesh]["primitives"][0]["attributes"]["TEXCOORD_0"];
		u32 indAccInd = m_dataJson["meshes"][indMesh]["primitives"][0]["indices"];

		// Use accessor indices to get all vertices components
		std::vector<f32> posVec = GetFloats(m_dataJson["accessors"][posAccInd]);
		vectors3 positions = GroupFloatsVec3(posVec);
		std::vector<f32> normalVec = GetFloats(m_dataJson["accessors"][normalAccInd]);
		vectors3  normals = GroupFloatsVec3(normalVec);
		std::vector<f32> texVec = GetFloats(m_dataJson["accessors"][texAccInd]);
		std::vector<glm::vec2> texUVs = GroupFloatsVec2(texVec);

		// Combine all the vertex components and also get the indices and textures
		std::vector<Vertex> vertices = AssembleVertices(positions, normals, texUVs);
		std::vector<u32> indices = GetIndices(m_dataJson["accessors"][indAccInd]);
		std::vector<Ref<Texture>> textures = GetTextures();

		// Combine the vertices, indices, and textures into a mesh
		meshes.push_back(Mould<Mesh>(vertices, indices, textures));
	}

	void GLTFLoader::TraverseNode(u32 nextNode, glm::mat4 matrix)
	{
		// Current node
		json node = m_dataJson["nodes"][nextNode];

		// Get translation if it exists
		glm::vec3 translation = glm::vec3(0.0f, 0.0f, 0.0f);
		if (node.find("translation") != node.end())
		{
			float transValues[3];
			for (unsigned int i = 0; i < node["translation"].size(); i++)
				transValues[i] = (node["translation"][i]);
			translation = glm::make_vec3(transValues);
		}
		// Get quaternion if it exists
		glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
		if (node.find("rotation") != node.end())
		{
			float rotValues[4] =
			{
				node["rotation"][3],
				node["rotation"][0],
				node["rotation"][1],
				node["rotation"][2]
			};
			rotation = glm::make_quat(rotValues);
		}
		// Get scale if it exists
		glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
		if (node.find("scale") != node.end())
		{
			float scaleValues[3];
			for (unsigned int i = 0; i < node["scale"].size(); i++)
				scaleValues[i] = (node["scale"][i]);
			scale = glm::make_vec3(scaleValues);
		}
		// Get matrix if it exists
		glm::mat4 matNode = glm::mat4(1.0f);
		if (node.find("matrix") != node.end())
		{
			float matValues[16];
			for (unsigned int i = 0; i < node["matrix"].size(); i++)
				matValues[i] = (node["matrix"][i]);
			matNode = glm::make_mat4(matValues);
		}

		// Initialize matrices
		glm::mat4 trans = glm::mat4(1.0f);
		glm::mat4 rot = glm::mat4(1.0f);
		glm::mat4 sca = glm::mat4(1.0f);

		// Use translation, rotation, and scale to change the initialized matrices
		trans = glm::translate(trans, translation);
		rot = glm::mat4_cast(rotation);
		sca = glm::scale(sca, scale);

		// Multiply all matrices together
		glm::mat4 matNextNode = matrix * matNode * trans * rot * sca;

		// Check if the node contains a mesh and if it does load it
		if (node.find("mesh") != node.end())
		{
			translationsMeshes.push_back(translation);
			rotationsMeshes.push_back(rotation);
			scalesMeshes.push_back(scale);
			matricesMeshes.push_back(matNextNode);

			loadMesh(node["mesh"]);
		}

		// Check if the node has children, and if it does, apply this function to them with the matNextNode
		if (node.find("children") != node.end())
		{
			for (unsigned int i = 0; i < node["children"].size(); i++)
				TraverseNode(node["children"][i], matNextNode);
		}
	}

	std::vector<u8> GLTFLoader::GetData()
	{
		// Create a place to store the raw text, and get the uri of the .bin file
		std::string bytesText;
		std::string uri = m_dataJson["buffers"][0]["uri"];

		// Store raw text data into bytesText
		std::string fileStr = std::string(m_file.GetPath());
		std::string fileDirectory = fileStr.substr(0, fileStr.find_last_of('/') + 1);
		bytesText = File::GetFileContent(fileDirectory + uri);

		// Transform the raw text data into bytes and put them in a vector
		std::vector<u8> data(bytesText.begin(), bytesText.end());
		return data;
	}

	std::vector<f32> GLTFLoader::GetFloats(json accessor)
	{
		std::vector<f32> floatVec;

		// Get properties from the accessor
		u32 buffViewInd = accessor.value("bufferView", 1);
		u32 count = accessor["count"];
		u32 accByteOffset = accessor.value("byteOffset", 0);
		std::string type = accessor["type"];

		// Get properties from the bufferView
		json bufferView = m_dataJson["bufferViews"][buffViewInd];
		u32 byteOffset = bufferView["byteOffset"];

		// Interpret the type and store it into numPerVert
		u32 numPerVert;
		if (type == "SCALAR") numPerVert = 1;
		else if (type == "VEC2") numPerVert = 2;
		else if (type == "VEC3") numPerVert = 3;
		else if (type == "VEC4") numPerVert = 4;
		else throw std::invalid_argument("Type is invalid (not SCALAR, VEC2, VEC3, or VEC4)");

		// Go over all the bytes in the data at the correct place using the properties from above
		u32 beginningOfData = byteOffset + accByteOffset;
		u32 lengthOfData = count * 4 * numPerVert;
		for (u32 i = beginningOfData; i < beginningOfData + lengthOfData; i)
		{
			u8 bytes[] = { m_data[i++], m_data[i++], m_data[i++], m_data[i++] };
			f32 value;
			std::memcpy(&value, bytes, sizeof(f32));
			floatVec.push_back(value);
		}

		return floatVec;
	}

	std::vector<u32> GLTFLoader::GetIndices(json accessor)
	{
		std::vector<u32> indices;

		// Get properties from the accessor
		u32 buffViewInd = accessor.value("bufferView", 0);
		u32 count = accessor["count"];
		u32 accByteOffset = accessor.value("byteOffset", 0);
		u32 componentType = accessor["componentType"];

		// Get properties from the bufferView
		json bufferView = m_dataJson["bufferViews"][buffViewInd];
		u32 byteOffset = bufferView["byteOffset"];

		// Get indices with regards to their type: unsigned int, unsigned short, or short
		u32 beginningOfData = byteOffset + accByteOffset;
		if (componentType == 5125)
		{
			for (u32 i = beginningOfData; i < byteOffset + accByteOffset + count * 4; i)
			{
				u8 bytes[] = { m_data[i++], m_data[i++], m_data[i++], m_data[i++] };
				u32 value;
				std::memcpy(&value, bytes, sizeof(u32));
				indices.push_back((u32)value);
			}
		}
		else if (componentType == 5123)
		{
			for (u32 i = beginningOfData; i < byteOffset + accByteOffset + count * 2; i)
			{
				u8 bytes[] = { m_data[i++], m_data[i++] };
				u16 value;
				std::memcpy(&value, bytes, sizeof(u16));
				indices.push_back((u32)value);
			}
		}
		else if (componentType == 5122)
		{
			for (u32 i = beginningOfData; i < byteOffset + accByteOffset + count * 2; i)
			{
				u32 bytes[] = { m_data[i++], m_data[i++] };
				s16 value;
				std::memcpy(&value, bytes, sizeof(s16));
				indices.push_back((u32)value);
			}
		}

		return indices;
	}

	std::vector<Ref<Texture>> GLTFLoader::GetTextures()
	{
		std::vector<Ref<Texture>> textures;

		std::string fileStr = std::string(m_file.GetPath());
		std::string fileDirectory = fileStr.substr(0, fileStr.find_last_of('/') + 1);

		// Go over all images
		for (u32 i = 0; i < m_dataJson["images"].size(); i++)
		{
			// uri of current texture
			std::string texPath = m_dataJson["images"][i]["uri"];

			// Check if the texture has already been loaded
			bool skip = false;
			for (u32 j = 0; j < loadedTexName.size(); j++)
			{
				if (loadedTexName[j] == texPath)
				{
					textures.push_back(loadedTex[j]);
					skip = true;
					break;
				}
			}

			// If the texture has been loaded, skip this
			if (!skip)
			{
				// Load diffuse texture
				if (texPath.find("baseColor") != std::string::npos)
				{
					Mold<Texture> diffuse = Mould<Texture>((fileDirectory + texPath).c_str(), "diffuse", loadedTex.size());
					textures.push_back(diffuse);
					loadedTex.push_back(diffuse);
					loadedTexName.push_back(texPath);
				}
				// Load specular texture
				else if (texPath.find("metallicRoughness") != std::string::npos)
				{
					Ref<Texture> specular = Mould<Texture>((fileDirectory + texPath).c_str(), "specular", loadedTex.size());
					textures.push_back(specular);
					loadedTex.push_back(specular);
					loadedTexName.push_back(texPath);
				}
			}
		}

		return textures;
	}

	std::vector<Vertex> GLTFLoader::AssembleVertices(vectors3 positions, vectors3 normals, std::vector<glm::vec2> texUVs)
	{
		std::vector<Vertex> vertices;
		for (s32 i = 0; i < positions.size(); i++)
		{
			vertices.push_back
			(
				Vertex
				{
					positions[i],
					normals[i],
					glm::vec3(1.0f, 1.0f, 1.0f),
					texUVs[i]
				}
			);
		}
		return vertices;
	}

	std::vector<glm::vec2> GLTFLoader::GroupFloatsVec2(std::vector<f32> floatVec)
	{
		std::vector<glm::vec2> vectors;
		for (s32 i = 0; i < floatVec.size(); i)
		{
			vectors.push_back(glm::vec2(floatVec[i++], floatVec[i++]));
		}
		return vectors;
	}

	std::vector<glm::vec3> GLTFLoader::GroupFloatsVec3(std::vector<f32> floatVec)
	{
		std::vector<glm::vec3> vectors;
		for (s32 i = 0; i < floatVec.size(); i)
		{
			vectors.push_back(glm::vec3(floatVec[i++], floatVec[i++], floatVec[i++]));
		}
		return vectors;
	}

	std::vector<glm::vec4> GLTFLoader::GroupFloatsVec4(std::vector<f32> floatVec)
	{
		std::vector<glm::vec4> vectors;
		for (s32 i = 0; i < floatVec.size(); i)
		{
			vectors.push_back(glm::vec4(floatVec[i++], floatVec[i++], floatVec[i++], floatVec[i++]));
		}
		return vectors;
	}
}
