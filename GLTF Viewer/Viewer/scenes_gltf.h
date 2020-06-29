#pragma once
#include <nlohmann/json.hpp>
#include <glm/glm.hpp>
#include <string>
#include <memory>
#include <vector>
#include <map>


#include "scenes_entity.h"
#include "common_bitmap.h"
#include "gl_entity.h"


namespace vnaon_scenes {

	class GLTF20 : public ScenesEntity {

	private:
		using json = nlohmann::json;

		class Sampler {
		public:
			std::string name;
			GLenum magFilter;
			GLenum minFilter;
			GLenum wrap_s;
			GLenum wrap_t;
		public:
			Sampler();
			~Sampler();
			vnaon_gl::GLTexture::SAMPLER get_sampler() const;
		};
		typedef std::shared_ptr<Sampler> Sampler_p;
		typedef std::vector<Sampler_p> SamplerArray;

		class Image {
		public:
			std::string name;
			std::string uri;
			std::string mimeType;
			GLintptr BufferView;
			vnaon_common::BitmapImage_p data;
		public:
			Image();
			~Image();
			vnaon_common::BitmapImage_p get_image() const;
		};
		typedef std::shared_ptr<Image> Image_p;
		typedef std::vector<Image_p> ImageArray;

		class Buffer {
		public:
			std::string name;
			std::string uri;
			GLsizei byteLength;
			GLchar *data;
		public:
			Buffer();
			~Buffer();
		};
		typedef std::shared_ptr<Buffer> Buffer_p;
		typedef std::vector<Buffer_p> BufferArray;

		class Texture {
		public:
			std::string name;
			GLintptr Sampler;
			GLintptr source;
			vnaon_gl::GLTexture_p data;
		public:
			Texture();
			~Texture();

			vnaon_gl::GLTexture_p get_texture() const;
		};
		typedef std::shared_ptr<Texture> Texture_p;
		typedef std::vector<Texture_p> TextureArray;

		class BufferView {
		public:
			std::string name;
			GLintptr Buffer;
			GLsizei byteLength;
			GLsizeiptr byteOffset;
			GLsizei byteStride;
			GLenum target;
		public:
			BufferView();
			~BufferView();
		};
		typedef std::shared_ptr<BufferView> BufferView_p;
		typedef std::vector<BufferView_p> BufferViewArray;

		class Material {
		public:
			struct texture_info {
				GLsizeiptr index;
				GLsizeiptr texCoord;
			};
			std::string name;
			struct {
				texture_info baseColorTexture;
				texture_info metallicRoughnessTexture;
				glm::vec4 baseColorFactor;
				GLfloat roughnessFactor;
				GLfloat metallicFactor;
			} pbrMetallicRoughness;
			struct {
				GLintptr index;
				GLintptr texCoord;
				GLfloat scale;
			}normalTexture;
			struct {
				GLsizeiptr index;
				GLsizeiptr texCoord;
				GLfloat strength;
			}occlusionTexture;
			texture_info emissiveTexture;
			glm::vec3 emissiveFactor;
			std::string alphaMode;
			GLfloat alphaCutoff;
			GLboolean doubleSided;
		public:
			Material();
			~Material();
		};
		typedef std::shared_ptr<Material> Material_p;
		typedef std::vector<Material_p> MaterialArray;

		class Accessor {
		public:
			std::string name;
			GLintptr BufferView;
			GLsizeiptr byteOffset;
			GLenum componentType;
			GLboolean normalized;
			GLint count;
			std::string type;
			std::vector<GLint> max;
			std::vector<GLint> min;
			struct {
				GLint count;
				struct {
					GLintptr BufferView;
					GLsizeiptr byteOffset;
					GLenum componentType;
				}indices;
				struct {
					GLintptr BufferView;
					GLsizeiptr byteOffset;
				}values;
			}sparse;
		public:
			Accessor();
			~Accessor();
		};
		typedef std::shared_ptr<Accessor> Accessor_p;
		typedef std::vector<Accessor_p> AccessorArray;

		// TODO: animation

		class Mesh {
			struct primitive {
				std::map<std::string, GLintptr> attributes;
				GLintptr indices;
				GLintptr Material;
				GLenum mode;
			};
		public:
			std::string name;
			std::vector<primitive> primitives;
			std::vector<GLfloat> weights;
		public:
			Mesh();
			~Mesh();
		};
		typedef std::shared_ptr<Mesh> Mesh_p;
		typedef std::vector<Mesh_p> MeshArray;

		// TODO: skin

		class Node {
		public:
			std::string name;
			std::vector<GLintptr> children;
			glm::mat4 matrix;
			GLintptr Mesh;
			glm::quat rotation;
			glm::vec3 scale;
			glm::vec3 translaion;
		public:
			Node();
			~Node();
		};
		typedef std::shared_ptr<Node> Node_p;
		typedef std::vector<Node_p> NodeArray;

		class Scene {
		public:
			std::string name;
			std::vector<GLintptr> nodes;
		public:
			Scene();
			~Scene();
		};
		typedef std::shared_ptr<Scene> Scene_p;
		typedef std::vector<Scene_p> SceneArray;

		protected:
			AccessorArray accessors;
			BufferArray buffers;
			BufferViewArray bufferViews;
			ImageArray images;
			MaterialArray materials;
			MeshArray meshes;
			NodeArray nodes;
			SamplerArray samplers;
			SceneArray scenes;
			TextureArray textures;
	};

}