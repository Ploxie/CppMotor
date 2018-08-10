#pragma once
#include <vector>

enum class ColorFormat
{
	R16_UINT = 0,
	R32_UINT,
	R32_SFLOAT,
	R32G32_SFLOAT,
	R32G32B32_SFLOAT,
	R32G32B32A32_SFLOAT,
	R32_SINT,
	R32G32_SINT,
	R32G32B32_SINT,
	R32G32B32A32_SINT,
	R8_UNORM,
	R8G8_UNORM,
	R8G8B8_UNORM,
	R8G8B8A8_UNORM,
	B8G8R8_UNORM,
	B8G8R8A8_UNORM,
	D32_SFLOAT
};

enum class PrimitiveTopology
{
	POINT_LIST = 0,
	LINE_LIST,
	LINE_STRIP,
	TRIANGLE_LIST,
	TRIANGLE_STRIP,
	TRIANGLE_FAN,
	LINE_LIST_WITH_ADJACENCY,
	LINE_STRIP_WITH_ADJACENCY,
	TRIANGLE_LIST_WITH_ADJACENCY,
	TRIANGLE_STRIP_WITH_ADJACENCY,
	PATCH_LIST
};

enum class PolygonDrawMode
{
	FILL = 0,
	LINE,
	POINT
};

enum class FrontFaceVertexWinding
{
	COUNTER_CLOCKWISE = 0,
	CLOCKWISE
};

enum class CullFaceSide
{
	NONE = 0,
	FRONT,
	BACK,
	FRONT_AND_BACK
};

enum class CompareOp
{
	NEVER = 0,
	LESS,
	EQUAL,
	LESS_OR_EQUAL,
	GREATER,
	NOT_EQUAL,
	GREATER_OR_EQUAL,
	ALWAYS
};

enum class BlendFactor
{
	ZERO = 0,
	ONE,
	SRC_COLOR,
	ONE_MINUS_SRC_COLOR,
	DST_COLOR,
	ONE_MINUS_DST_COLOR,
	SRC_ALPHA,
	ONE_MINUS_SRC_ALPHA,
	DST_ALPHA,
	ONE_MINUS_DST_ALPHA,
	SRC_ALPHA_SATURATE
};

enum class BlendOp
{
	ADD = 0,
	SUBTRACT,
	REVERSE_SUBTRACT,
	MIN,
	MAX
};

enum class VertexInputRate 
{
	VERTEX = 0,
	INSTANCE
};

struct BindingDescription 
{

	uint32_t binding;
	uint32_t stride;
	VertexInputRate inputRate = VertexInputRate::VERTEX;
};

struct AttributeDescription
{
	unsigned int location;
	unsigned int binding;
	ColorFormat format;
	unsigned int offset;
};

struct VertexInputInfo
{
	std::vector<BindingDescription> bindingDescriptions;
	std::vector<AttributeDescription> attributeDescriptions;
};

struct AttachmentColorBlendProperties
{
	bool blendEnable = false;
	BlendFactor srcColorBlendFactor;
	BlendFactor dstColorBlendFactor;
	BlendOp colorBlendOp;
	BlendFactor srcAlphaBlendFactor;
	BlendFactor dstAlphaBlendFactor;
	BlendOp alphaBlendOp;
	bool colorWriteMaskR = true;
	bool colorWriteMaskG = true;
	bool colorWriteMaskB = true;
	bool colorWriteMaskA = true;
};

struct GraphicsPipelineProperties
{
	VertexInputInfo vertexInputInfo;
	PrimitiveTopology topology = PrimitiveTopology::TRIANGLE_LIST;
	PolygonDrawMode polygonDrawMode = PolygonDrawMode::FILL;
	FrontFaceVertexWinding frontFaceVertexWinding = FrontFaceVertexWinding::COUNTER_CLOCKWISE;
	CullFaceSide cullFaceSide = CullFaceSide::BACK;
	float lineWidth = 1.0f;
	bool dynamicViewPort = true;
	bool dynamicScissor = true;
	bool dynamicLineWidth = false;
	bool dynamicDepthBias = false;
	bool dynamicBlendConstants = false;
	bool dynamicDepthBounds = false;

	std::vector<AttachmentColorBlendProperties> attachmentColorBlendProperties;

	bool depthTestEnable = true;
	bool depthWriteEnable = true;
	CompareOp depthCompareOp = CompareOp::LESS;
	bool depthBoundsTestEnable = false;
	float minDepthBounds = 0.0f;
	float maxDepthBounds = 1.0f;
};