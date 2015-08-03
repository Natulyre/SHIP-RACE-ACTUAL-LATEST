
// HLSL - High Level Shading Language

// Effet de post-process

// Types
// float
// float2
// float3
// float4
// float4x4
// int
// bool

uniform extern float4x4 gWVP;
uniform extern float gTime;
uniform extern float3 gEyePos;
uniform extern float4 gFogColor;

float minDist = 10.0f;
float maxDist = 100.0f;

// Amplitude
static float a[2] = { 0.8f, 0.2f };

// Angular Wave number
static float k[2] = { 1.0f, 8.0f };

// Angular frequency
static float w[2] = { 1.0f, 8.0f };

// Phase shift
static float p[2] = { 0.0f, 1.0f };


struct OutputVS
{
				// SEMANTIC
	float4 posH: POSITION0;
	float4 color: COLOR0;
	float fogLerp : TEXCOORD3;
};

float SumOfRadialSineWave(float x, float z)
{
	// Distance of the vertex from the wave source
	float d = sqrt(x*x + z*z);

	// Sum the waves;
	float sum = 0.0f;
	for (int i = 0; i < 2; i++)
	{
		sum += a[i] * sin(k[i] * d - gTime*w[i] + p[i]);
	}
	return sum;
}

float4 GetColorFromHeight(float y)
{
	if (abs(y) <= -10.0f)
		return float4(1.0f, 0.96f, 0.62f, 1.0f); // Beach Sand
	else if (abs(y) <= 5.0f)
		return float4(0.48f, 0.77f, 0.46f, 1.0f); // Light Yellow green
	else if (abs(y) <= 12.0f)
		return float4(0.0f, 1.0f, 0.0f, 1.0f); // GREEN
	else if (abs(y) <= 20.0f)
		return float4(1.0f, 0.0f, 0.0f, 1.0f); // RED
	else
		return float4(1.0f, 1.0f, 0.0f, 1.0f);
}

// Fonction VertexShader
OutputVS TransformSineVS(float3 posL: POSITION0, float4 color : COLOR0)
{
	OutputVS outVS = (OutputVS)0;

	posL.y = SumOfRadialSineWave(posL.x, posL.z);

	outVS.posH = mul(float4(posL, 1.0f), gWVP);
	outVS.color = GetColorFromHeight(posL.y);

	return outVS;
}

OutputVS TransformVS(float3 posL: POSITION0, float4 color: COLOR0)
{
	OutputVS outVS = (OutputVS)0;
	outVS.posH = mul(float4(posL, 1.0f), gWVP);
	outVS.color = GetColorFromHeight(posL.y);

	float dist = distance(posL, gEyePos);
	outVS.fogLerp = saturate((dist - minDist) / (maxDist - minDist));

	return outVS;
}

OutputVS TransformVS_Scale(float3 posL: POSITION0, float4 color : COLOR0)
{
	OutputVS outVS = (OutputVS)0;
	outVS.posH = mul(float4(posL * 1.01f, 1.0f), gWVP);
	outVS.color = color;
	return outVS;
}

float4 TransformPS(OutputVS inVS): COLOR0
{
	float4 finalColor = lerp(inVS.color, gFogColor, inVS.fogLerp);
	return finalColor;
}

float4 TransformPS_Black(OutputVS inVS) : COLOR0
{
	float4 finalColor = lerp((float4)0, gFogColor, inVS.fogLerp);
	return finalColor;
}
 
// Techniques
technique TransformTech
{
	pass P0
	{
		vertexShader = compile vs_2_0 TransformVS();
		pixelShader = compile ps_2_0 TransformPS();

		FillMode = Solid;
	}

	pass P1
	{
		vertexShader = compile vs_2_0 TransformVS();
		pixelShader = compile ps_2_0 TransformPS_Black();
		FillMode = WireFrame;
	}
}

technique TransformTechSine
{
	pass P0
	{
		vertexShader = compile vs_2_0 TransformSineVS();
		pixelShader = compile ps_2_0 TransformPS();
		FillMode = Solid;
	}

	pass P1
	{
		vertexShader = compile vs_2_0 TransformSineVS();
		pixelShader = compile ps_2_0 TransformPS_Black();
		FillMode = WireFrame;
	}
}