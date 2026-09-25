Texture2D Texture : register(t0);
SamplerState Sampler : register(s0);

cbuffer ConstBuffer : register(b0)
{
	float2 textureSize;
	float time;
};

struct PSInput
{
	float4 Color : COLOR0;
	float2 TexCoord : TEXCOORD0;
};

float4 main(PSInput input) : SV_Target
{
	return float4(input.TexCoord, 0.0f, 1.0f);
}