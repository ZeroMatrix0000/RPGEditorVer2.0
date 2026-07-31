Texture2D Texture : register(t0);
SamplerState Sampler : register(s0);

cbuffer ConstBuffer : register(b0)
{
	float2 textureSize;
};

struct PSInput
{
	float4 Color : COLOR0;
	float2 TexCoord : TEXCOORD0;
};

float4 main(PSInput input) : SV_Target
{
	float2 uv = input.TexCoord;
	float alpha = 0.0f;
	float4 base = Texture.Sample(Sampler, uv);
	float interval = 2.0f;
	
	float4 blur = base - 0.5f;

	for (int i = 1; i < 10; i++)
	{
		blur += (Texture.Sample(Sampler, uv + float2(-1.0f, -1.0f) / textureSize * interval * i) - 0.5f) / i;
		blur += (Texture.Sample(Sampler, uv + float2(-1.0f,  0.0f) / textureSize * interval * i) - 0.5f) / i;
		blur += (Texture.Sample(Sampler, uv + float2(-1.0f,  1.0f) / textureSize * interval * i) - 0.5f) / i;
		blur += (Texture.Sample(Sampler, uv + float2( 0.0f, -1.0f) / textureSize * interval * i) - 0.5f) / i;
		blur += (Texture.Sample(Sampler, uv + float2( 0.0f,  1.0f) / textureSize * interval * i) - 0.5f) / i;
		blur += (Texture.Sample(Sampler, uv + float2( 1.0f, -1.0f) / textureSize * interval * i) - 0.5f) / i;
		blur += (Texture.Sample(Sampler, uv + float2( 1.0f,  0.0f) / textureSize * interval * i) - 0.5f) / i;
		blur += (Texture.Sample(Sampler, uv + float2( 1.0f,  1.0f) / textureSize * interval * i) - 0.5f) / i;
	}
	
	blur /= 20.0f;
	
	float4 color = base + blur;
	
	return color * input.Color;
}