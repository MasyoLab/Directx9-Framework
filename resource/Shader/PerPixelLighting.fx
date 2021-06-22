//==========================================================================
// �p�[�s�N�Z���E���C�e�B���O [PerPixelLighting.fx]
// author: MasyoLab
//==========================================================================

//==========================================================================
// �O���[�o���ϐ�
//==========================================================================
float4x4 World; // ���[���h�ϊ��s��
float4x4 View; // �J�����ϊ��s��
float4x4 Projection; // �v���W�F�N�V�����ϊ��s��

bool TexFlag; // �e�N�X�`���̂���Ȃ� false:�Ȃ� true:����
float4 CameraPos; // �J�����ʒu

// ��
float4 Diffuse; // �f�B�t���[�Y
float4 Ambient; // ����
float4 Specular; // �X�y�L�����[
float4 Emmisive; // �G�~�b�V�u

float3 LightDir; // ���s�����̕���

// �}�e���A��
float4 DiffuseMatrix; // �f�B�t���[�Y��
float4 EmmisiveMatrix; // �G�~�b�V�u��
float4 AmbientMatrix; // ����
float4 SpecularMatrix; // �X�y�L�����[
float Power; // �X�y�L�����[���̃p���[�l

texture Texture; // �e�N�X�`��

//==========================================================================
// �T���v���[
//==========================================================================
sampler Sampler = sampler_state
{
    texture = <Texture>;
    MinFilter = LINEAR; // ���j�A�t�B���^�i�k�����j
    MagFilter = LINEAR; // ���j�A�t�B���^�i�g�厞�j
};

struct VS_Param
{
    float4 pos : POSITION;
    float2 tex : TEXCOORD0;
    float3 normal : TEXCOORD1;
    float3 posforps : TEXCOORD2;
};

//==========================================================================
// ���_�V�F�[�_
//==========================================================================
VS_Param main(
in float3 in_pos : POSITION,
in float3 in_normal : NORMAL,
in float2 in_tex1 : TEXCOORD0)
{
    VS_Param Out;

	// ���W�ϊ�
    Out.pos = mul(float4(in_pos, 1.0f), World);
    Out.posforps = Out.pos.xyz;
    Out.pos = mul(Out.pos, View);
    Out.pos = mul(Out.pos, Projection);

    // �e�N�X�`�����W�����̂܂܏o�͂���
    Out.tex = in_tex1;

    // �@�������[���h��ԏ�̃x�N�g���ɕϊ����āA�P�ʃx�N�g����
    Out.normal = normalize(mul(in_normal, (float3x3) World));

    return Out;
}

//==========================================================================
// �s�N�Z���V�F�[�_
//==========================================================================
float4 psPerPixelLighting(in VS_Param In) : COLOR0
{
    float3 N; // ���[���h��ԏ�̖@���x�N�g��
    float3 L; // ���̍������ޕ���	
    float3 P; // ���_���W
    float3 V; // �����x�N�g��
    float3 H; // �n�[�t�x�N�g��
    float4 Out;

    P = In.posforps;
    N = normalize(In.normal);

	// ���s���̍������ޕ���	�P�ʃx�N�g����
    L = normalize(-LightDir);

    // �����x�N�g�������߂�
    V = CameraPos.xyz - P; // �J�������W-���_���W

    // ���K��
    V = normalize(V);

    // �n�[�t�x�N�g�������߂�
    H = normalize(V + L);

    // �f�B�t���[�Y�J���[�����߂�
    float4 diffuse = Diffuse * DiffuseMatrix * max(0.0, dot(L, N));

    // �X�y�L�����[���ɂ��F���v�Z
    float4 specular = Specular * SpecularMatrix * pow(max(0, dot(N, H)), Power);

    if (TexFlag)
    {
        float4 tex_color = tex2D(Sampler, In.tex);

		// �e�N�X�`���̐F�ƒ��_�̐F���|�����킹��
        Out = saturate(diffuse * tex_color + specular);
    }
    else
    {
        Out = saturate(diffuse + specular);
    }

    return Out;
}

//==========================================================================
// �V�F�[�_�[�̃p�b�P�[�W
//==========================================================================
technique PerPixelLighting
{
    pass P0
    {
        // �g�p����V�F�[�_�[��n��
        VertexShader = compile vs_3_0 main();
        PixelShader = compile ps_3_0 psPerPixelLighting();
        
        // Effect States
        AlphaBlendEnable = false;
        SrcBlend = SRCALPHA;
        DestBlend = INVSRCALPHA;
    }
}
