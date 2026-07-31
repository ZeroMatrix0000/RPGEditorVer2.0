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
	static const float PI = 3.14159265359f;
	
	float2 uv = input.TexCoord;
	float4 color = Texture.Sample(Sampler, uv);
	
	float2 pos = (uv * textureSize + float2(2.0f, 1.0f) * time * 50.0f) % 200.0f - 100.0f;
	float r = length(pos);
	float t = atan2(pos.y, pos.x) + 2.0f * PI + time;
	float s = step(r, (abs(t % (0.4f * PI) - 0.2f * PI) + 0.5f) * 75.0f);
	
	color.rgb = lerp(color.rgb, float3(1.0f, 0.5f, 0.0f), s * 0.2f);
	
	return color * input.Color;
}