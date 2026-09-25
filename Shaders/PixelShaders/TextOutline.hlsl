Texture2D Texture : register(t0);
SamplerState Sampler : register(s0);

struct PSInput
{
    float4 Color : COLOR0;
    float2 TexCoord : TEXCOORD0;
};

float4 main(PSInput input) : SV_Target
{
    return Texture.Sample(Sampler, input.TexCoord);
}