#pragma once
#include <nlohmann/json.hpp>
#include <glm/glm.hpp>
#include <string>
#include <memory>
#include <vector>
#include <map>


#include "scenes_object.h"
#include "bitmap_img.h"
#include "GLobject.h"


namespace vnaon_scenes {

	class GLTF20 : public scenes_object {

	private:
		using Json = nlohmann::json;

		class sampler {
		public:
			std::string name;
			GLenum magFilter;
			GLenum minFilter;
			GLenum wrapS;
			GLenum wrapT;
		public:
			sampler();
			~sampler();
			vnaon_gl::GLtexture::SAMPLER get_sampler() const;
		};
		typedef std::shared_ptr<sampler> p_sampler;
		typedef std::vector<p_sampler> sampler_array;

		class image {
		public:
			std::string name;
			std::string uri;
			std::string mimeType;
			GLintptr bufferView;
			vnaon_common::p_bitmap data;
		public:
			image();
			~image();
			vnaon_common::p_bitmap get_image() const;
		};
		typedef std::shared_ptr<image> p_image;
		typedef std::vector<p_image> image_array;

		class buffer {
		public:
			std::string name;
			std::string uri;
			GLsizei byteLength;
			GLchar *data;
		public:
			buffer();
			~buffer();
		};
		typedef std::shared_ptr<buffer> p_buffer;
		typedef std::vector<p_buffer> buffer_array;

		class texture {
		public:
			std::string name;
			GLintptr sampler;
			GLintptr source;
			vnaon_gl::p_texture data;
		public:
			texture();
			~texture();

			vnaon_gl::p_texture get_texture() const;
		};
		typedef std::shared_ptr<texture> p_texture;
		typedef std::vector<p_texture> texture_array;

		class bufferView {
		public:
			std::string name;
			GLintptr buffer;
			GLsizei byteLength;
			GLsizeiptr byteOffset;
			GLsizei byteStride;
			GLenum target;
		public:
			bufferView();
			~bufferView();
		};
		typedef std::shared_ptr<bufferView> p_bufferView;
		typedef std::vector<p_bufferView> bufferView_array;

		class material {
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
			material();
			~material();
		};
		typedef std::shared_ptr<material> p_material;
		typedef std::vector<p_material> material_array;

		class accessor {
		public:
			std::string name;
			GLintptr bufferView;
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
					GLintptr bufferView;
					GLsizeiptr byteOffset;
					GLenum componentType;
				}indices;
				struct {
					GLintptr bufferView;
					GLsizeiptr byteOffset;
				}values;
			}sparse;
		public:
			accessor();
			~accessor();
		};
		typedef std::shared_ptr<accessor> p_accessor;
		typedef std::vector<p_accessor> accessor_array;

		// TODO: animation
		//class animation;
		//typedef std::shared_ptr<animation> p_animation;
		//typedef std::vector<p_animation> animation_array;

		class mesh {
			struct primitive {
				std::map<std::string, GLintptr> attributes;
				GLintptr indices;
				GLintptr material;
				GLenum mode;
			};
		public:
			std::string name;
			std::vector<primitive> primitives;
			std::vector<GLfloat> weights;
		public:
			mesh();
			~mesh();
		};
		typedef std::shared_ptr<mesh> p_mesh;
		typedef std::vector<p_mesh> mesh_array;

		// TODO: skin
		//class skin;
		//typedef std::shared_ptr<skin> p_skin;
		//typedef std::vector<p_skin> skin_array;

		class node {
		public:
			std::string name;
			std::vector<GLintptr> children;
			glm::mat4 matrix;
			GLintptr mesh;
			glm::quat rotation;
			glm::vec3 scale;
			glm::vec3 translaion;
		public:
			node();
			~node();
		};
		typedef std::shared_ptr<node> p_node;
		typedef std::vector<p_node> node_array;

		class scene {
		public:
			std::string name;
			std::vector<GLintptr> nodes;
		public:
			scene();
			~scene();
		};
		typedef std::shared_ptr<scene> p_scene;
		typedef std::vector<p_scene> scene_array;

		protected:
			accessor_array accessors;
			buffer_array buffers;
			bufferView_array bufferViews;
			image_array images;
			material_array materials;
			mesh_array meshes;
			node_array nodes;
			sampler_array samplers;
			scene_array scenes;
			texture_array textures;
	};

}