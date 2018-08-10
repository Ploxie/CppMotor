#include "stdafx.h"
#include "VulkanUtil.h"


namespace Vulkan
{
	namespace VulkanUtil
	{

		std::string translateVulkanResult(VkResult result) {
			switch (result) {
				// Success codes
			case VK_SUCCESS:
				return "Command successfully completed.";
			case VK_NOT_READY:
				return "A fence or query has not yet completed.";
			case VK_TIMEOUT:
				return "A wait operation has not completed in the specified time.";
			case VK_EVENT_SET:
				return "An event is signaled.";
			case VK_EVENT_RESET:
				return "An event is unsignaled.";
			case VK_INCOMPLETE:
				return "A return array was too small for the result.";
			case VK_SUBOPTIMAL_KHR:
				return "A swapchain no longer matches the surface properties exactly, but can still be used to present to the surface successfully.";

				// Error codes
			case VK_ERROR_OUT_OF_HOST_MEMORY:
				return "A host memory allocation has failed.";
			case VK_ERROR_OUT_OF_DEVICE_MEMORY:
				return "A device memory allocation has failed.";
			case VK_ERROR_INITIALIZATION_FAILED:
				return "Initialization of an object could not be completed for implementation-specific reasons.";
			case VK_ERROR_DEVICE_LOST:
				return "The logical or physical device has been lost.";
			case VK_ERROR_MEMORY_MAP_FAILED:
				return "Mapping of a memory object has failed.";
			case VK_ERROR_LAYER_NOT_PRESENT:
				return "A requested layer is not present or could not be loaded.";
			case VK_ERROR_EXTENSION_NOT_PRESENT:
				return "A requested extension is not supported.";
			case VK_ERROR_FEATURE_NOT_PRESENT:
				return "A requested feature is not supported.";
			case VK_ERROR_INCOMPATIBLE_DRIVER:
				return "The requested version of Vulkan is not supported by the driver or is otherwise incompatible for implementation-specific reasons.";
			case VK_ERROR_TOO_MANY_OBJECTS:
				return "Too many objects of the type have already been created.";
			case VK_ERROR_FORMAT_NOT_SUPPORTED:
				return "A requested format is not supported on this device.";
			case VK_ERROR_SURFACE_LOST_KHR:
				return "A surface is no longer available.";
			case VK_ERROR_NATIVE_WINDOW_IN_USE_KHR:
				return "The requested window is already connected to a VkSurfaceKHR, or to some other non-Vulkan API.";
			case VK_ERROR_OUT_OF_DATE_KHR:
				return "A surface has changed in such a way that it is no longer compatible with the swapchain, and further presentation requests using the "
					"swapchain will fail. Applications must query the new surface properties and recreate their swapchain if they wish to continue"
					"presenting to the surface.";
			case VK_ERROR_INCOMPATIBLE_DISPLAY_KHR:
				return "The display used by a swapchain does not use the same presentable image layout, or is incompatible in a way that prevents sharing an"
					" image.";
			case VK_ERROR_VALIDATION_FAILED_EXT:
				return "A validation layer found an error.";
			default:
				return "Unknown error " + std::to_string(result);
			}
		}

		VkPrimitiveTopology getTopology(PrimitiveTopology topology)
		{
			switch (topology) {
			case PrimitiveTopology::POINT_LIST:
				return VK_PRIMITIVE_TOPOLOGY_POINT_LIST;
			case PrimitiveTopology::LINE_LIST:
				return VK_PRIMITIVE_TOPOLOGY_LINE_LIST;
			case PrimitiveTopology::LINE_STRIP:
				return VK_PRIMITIVE_TOPOLOGY_LINE_STRIP;
			case PrimitiveTopology::TRIANGLE_LIST:
				return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
			case PrimitiveTopology::TRIANGLE_STRIP:
				return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP;
			case PrimitiveTopology::TRIANGLE_FAN:
				return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_FAN;
			case PrimitiveTopology::LINE_LIST_WITH_ADJACENCY:
				return VK_PRIMITIVE_TOPOLOGY_LINE_LIST_WITH_ADJACENCY;
			case PrimitiveTopology::LINE_STRIP_WITH_ADJACENCY:
				return VK_PRIMITIVE_TOPOLOGY_LINE_STRIP_WITH_ADJACENCY;
			case PrimitiveTopology::TRIANGLE_LIST_WITH_ADJACENCY:
				return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST_WITH_ADJACENCY;
			case PrimitiveTopology::TRIANGLE_STRIP_WITH_ADJACENCY:
				return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP_WITH_ADJACENCY;
			case PrimitiveTopology::PATCH_LIST:
				return VK_PRIMITIVE_TOPOLOGY_PATCH_LIST;
			default:
				throw std::runtime_error("Unsupported PrimitiveTopology");
			}
		}

		VkPolygonMode getPolygonDrawMode(PolygonDrawMode drawMode)
		{
			switch (drawMode) {
			case PolygonDrawMode::FILL:
				return VK_POLYGON_MODE_FILL;
			case PolygonDrawMode::LINE:
				return VK_POLYGON_MODE_LINE;
			case PolygonDrawMode::POINT:
				return VK_POLYGON_MODE_POINT;
			default:
				throw std::runtime_error("Unsupported PolygonDrawMode");
			}
		}

		VkFrontFace getFrontFaceVertexWinding(FrontFaceVertexWinding vertexWinding)
		{
			switch (vertexWinding) {
			case FrontFaceVertexWinding::COUNTER_CLOCKWISE:
				return VK_FRONT_FACE_COUNTER_CLOCKWISE;
			case FrontFaceVertexWinding::CLOCKWISE:
				return VK_FRONT_FACE_CLOCKWISE;
			default:
				throw std::runtime_error("Unsupported FrontFaceVertexWinding");
			}
		}

		VkCullModeFlagBits getCullMode(CullFaceSide cullFaceSide)
		{
			switch (cullFaceSide) {
			case CullFaceSide::BACK:
				return VK_CULL_MODE_BACK_BIT;
			case CullFaceSide::FRONT:
				return VK_CULL_MODE_FRONT_BIT;
			case CullFaceSide::FRONT_AND_BACK:
				return VK_CULL_MODE_FRONT_AND_BACK;
			case CullFaceSide::NONE:
				return VK_CULL_MODE_NONE;
			default:
				throw std::runtime_error("Unsupported CullFaceSide");
			}
		}

		VkCompareOp getCompareOp(CompareOp compareOp)
		{
			switch (compareOp) {
			case CompareOp::NEVER:
				return VK_COMPARE_OP_NEVER;
			case CompareOp::LESS:
				return VK_COMPARE_OP_LESS;
			case CompareOp::EQUAL:
				return VK_COMPARE_OP_EQUAL;
			case CompareOp::LESS_OR_EQUAL:
				return VK_COMPARE_OP_LESS_OR_EQUAL;
			case CompareOp::GREATER:
				return VK_COMPARE_OP_GREATER;
			case CompareOp::NOT_EQUAL:
				return VK_COMPARE_OP_NOT_EQUAL;
			case CompareOp::GREATER_OR_EQUAL:
				return VK_COMPARE_OP_GREATER_OR_EQUAL;
			case CompareOp::ALWAYS:
				return VK_COMPARE_OP_ALWAYS;
			default:
				throw std::runtime_error("Unsupported CullFaceSide");
			}
		}

		VkBlendFactor getBlendFactor(BlendFactor blendFactor)
		{
			switch (blendFactor) {
			case BlendFactor::ZERO:
				return VK_BLEND_FACTOR_ZERO;
			case BlendFactor::ONE:
				return VK_BLEND_FACTOR_ONE;
			case BlendFactor::SRC_COLOR:
				return VK_BLEND_FACTOR_SRC_COLOR;
			case BlendFactor::ONE_MINUS_SRC_COLOR:
				return VK_BLEND_FACTOR_ONE_MINUS_SRC_COLOR;
			case BlendFactor::DST_COLOR:
				return VK_BLEND_FACTOR_DST_COLOR;
			case BlendFactor::ONE_MINUS_DST_COLOR:
				return VK_BLEND_FACTOR_ONE_MINUS_DST_COLOR;
			case BlendFactor::SRC_ALPHA:
				return VK_BLEND_FACTOR_SRC_ALPHA;
			case BlendFactor::ONE_MINUS_SRC_ALPHA:
				return VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
			case BlendFactor::DST_ALPHA:
				return VK_BLEND_FACTOR_DST_ALPHA;
			case BlendFactor::ONE_MINUS_DST_ALPHA:
				return VK_BLEND_FACTOR_ONE_MINUS_DST_ALPHA;
			case BlendFactor::SRC_ALPHA_SATURATE:
				return VK_BLEND_FACTOR_SRC_ALPHA_SATURATE;
			default:
				throw std::runtime_error("Unsupported BlendFactor");
			}
		}

		VkBlendOp getBlendOp(BlendOp blendOp)
		{
			switch (blendOp) {
			case BlendOp::ADD:
				return VK_BLEND_OP_ADD;
			case BlendOp::SUBTRACT:
				return VK_BLEND_OP_SUBTRACT;
			case BlendOp::REVERSE_SUBTRACT:
				return VK_BLEND_OP_REVERSE_SUBTRACT;
			case BlendOp::MIN:
				return VK_BLEND_OP_MIN;
			case BlendOp::MAX:
				return VK_BLEND_OP_MAX;
			default:
				throw std::runtime_error("Unsupported BlendOp");
			}
		}

		VkVertexInputRate getVertexInputRate(VertexInputRate vertexInputRate)
		{
			switch (vertexInputRate) {
			case VertexInputRate::VERTEX:
				return VK_VERTEX_INPUT_RATE_VERTEX;
			case VertexInputRate::INSTANCE:
				return VK_VERTEX_INPUT_RATE_INSTANCE;
			default:
				throw std::runtime_error("Unsupported VertexInputRate");
			}
		}

		VkFormat getColorFormat(ColorFormat colorFormat)
		{
			switch (colorFormat) {
			case ColorFormat::R32_SFLOAT:
				return VK_FORMAT_R32_SFLOAT;
			case ColorFormat::R32G32_SFLOAT:
				return VK_FORMAT_R32G32_SFLOAT;
			case ColorFormat::R32G32B32_SFLOAT:
				return VK_FORMAT_R32G32B32_SFLOAT;
			case ColorFormat::R32G32B32A32_SFLOAT:
				return VK_FORMAT_R32G32B32A32_SFLOAT;

			case ColorFormat::R32_SINT:
				return VK_FORMAT_R32_SINT;
			case ColorFormat::R32G32_SINT:
				return VK_FORMAT_R32G32_SINT;
			case ColorFormat::R32G32B32_SINT:
				return VK_FORMAT_R32G32B32_SINT;
			case ColorFormat::R32G32B32A32_SINT:
				return VK_FORMAT_R32G32B32A32_SINT;

			case ColorFormat::R8_UNORM:
				return VK_FORMAT_R8_UNORM;
			case ColorFormat::R8G8_UNORM:
				return VK_FORMAT_R8G8_UNORM;
			case ColorFormat::R8G8B8_UNORM:
				return VK_FORMAT_R8G8B8_UNORM;
			case ColorFormat::R8G8B8A8_UNORM:
				return VK_FORMAT_R8G8B8A8_UNORM;

			case ColorFormat::B8G8R8_UNORM:
				return VK_FORMAT_B8G8R8_UNORM;
			case ColorFormat::B8G8R8A8_UNORM:
				return VK_FORMAT_B8G8R8A8_UNORM;

			case ColorFormat::D32_SFLOAT:
				return VK_FORMAT_D32_SFLOAT;
			default:
				throw std::runtime_error("Unsupported VertexInputRate");
			}
		}

	}
}