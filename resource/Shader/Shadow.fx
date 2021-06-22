//==========================================================================
// �e [Shadow.fx]
// author: MasyoLab
//==========================================================================

//==========================================================================
// �O���[�o���ϐ�
//==========================================================================
float4x4 World; // ���[���h�ϊ��s��
float4x4 CameraView; // �J�����ϊ��s��
float4x4 CameraProjection; // �v���W�F�N�V�����ϊ��s��
float4x4 LightView; // �������猩���ϊ��s��
float4x4 LightProjection; //  �����̃v���W�F�N�V�����ϊ��s��

float3 LightDir; // ���s�����̕���

float3 LightDiffuse; // ����Diffuse
float3 LightAmbient; // ����Ambient

float3 MaterialDiffuse; // �}�e���A����Diffusec
float3 MaterialAmbient; // �}�e���A����Ambient

float Bias = 0.0f; // �o�C�A�X

texture Texture; // �e�N�X�`��

sampler Sampler = sampler_state
{
    texture = <Texture>;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = LINEAR;
    AddressU = Clamp;
    AddressV = Clamp;
    AddressW = Clamp;
};

struct Output
{
    float4 pos : POSITION;
    float4 color : COLOR0;
    float4 shadowmap : TEXCOORD0;
    float4 color2 : TEXCOORD1; //w=�e�̔Z��
};

//==========================================================================
// ���_�V�F�[�_
//==========================================================================
Output main(
in float3 pos : POSITION,
in float3 normal : NORMAL)
{
    Output Out;

    float4 p = mul(float4(pos, 1.0f), World);
    Out.pos = mul(mul(p, CameraView), CameraProjection);

    float3 n = mul(normal, (float3x3) World);
    n = normalize(n);

    float k = max(dot(LightDir.xyz, n), 0.0f);
    float4 color = k * LightDiffuse * MaterialDiffuse;
    color += LightAmbient * MaterialAmbient;
    Out.color = color;
    
    //�e�̔Z���i�K����3�悵�Ă݂��j
    Out.color2.w = k * k * k * 0.6f;
	
    p = mul(float4(pos, 1.0f), World);
    p = mul(mul(p, LightView), LightProjection);
    Out.shadowmap = p;

    return Out;
}

//==========================================================================
// �s�N�Z���V�F�[�_
//==========================================================================
float4 psShadow(Output input) : COLOR
{
    float w = 1.0f / input.shadowmap.w;
    float2 tex;
    tex.x = (1.0f + input.shadowmap.x * w) * 0.5f;
    tex.y = (1.0f - input.shadowmap.y * w) * 0.5f;
    float z = tex2D(Sampler, tex).x;

    float color = input.color;
    if (input.shadowmap.z * w > z + Bias)
        color = color * (1.0f - input.color2.w); //�e�̔Z�����|����

    return color;
}

//==========================================================================
// �V�F�[�_�[�̃p�b�P�[�W
//==========================================================================
technique Shadow
{
    pass P0
    {
        // �g�p����V�F�[�_�[��n��
        VertexShader = compile vs_3_0 main();
        PixelShader = compile ps_3_0 psShadow();
        
        // Effect States
        AlphaBlendEnable = true;
        SrcBlend = SRCALPHA;
        DestBlend = INVSRCALPHA;
    }
}
