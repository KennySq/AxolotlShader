struct VertexShaderInput
{
    float3 pos : POSITION;
    float2 tex : TEXCOORD;
};

struct PixelShaderInput
{
    float4 pos : SV_POSITION;
    float2 tex : TEXCOORD;
};

float4x4 WorldViewProjection;

cbuffer Generals
{
    float4x4 Projection;
};

PixelShaderInput VS(VertexShaderInput input)
{
    PixelShaderInput output;

    output.pos = mul(float4(input.pos, 1), WorldViewProjection);
    output.pos = mul(output.pos, Projection);
    output.tex = input.tex;

    return output;
}