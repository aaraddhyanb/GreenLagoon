--[[
	This file defines all of the assets for the renderer and how they're built

	There is a single list of assets, but within that list assets are grouped according to their type.
	The string used for each asset type determines the folder that those assets will be in;
	for example, using the string "Textures" means that the asset build process will:
		1) Look in Assets/Textures/ for the source texture files
		2) Build the target texture files into data/Textures/

	Within each asset type, the asset build process will look for the following:
		"tool" -
			This should be the name of the executable tool that is used to build the asset type.
			For example, "TextureBuilder" means that tools/TextureBuilder.exe will be used
		"extensions" -
			This defines a "source" and a "target" file extension.
			The source extension tells the asset build process what file type to look for in Assets/Textures,
			and the target extension tells what file type to create in data/Textures/
			(these are often different, but can be the same if the tool just copies files)
		"names" -
			This is a list of the actual assets that should be built.
			Each name should be the file name of the asset (without the directory or the file extension).
			For example, if there were a texture named "example1":
				* The source asset would be Assets/Textures/example1.png
				* The target asset would be data/Textures/example1.png
		"shouldAssetsAlwaysBeBuilt" -
			This is an optional boolean value, and if not found will default to false.
			Usually assets should only be built if they need to be
			(e.g. the built data file doesn't exist or the source asset has changed);
			when you are changing code for an asset-building executable, however,
			you will want to change this default behavior so that assets always get built
			regardless of dependencies.
]]

-- The following does the same thing that is documented above,
-- but it applies to _all_ asset types.
-- In other words, if it is set to true then _every_ asset will be built
-- _every_ time the solution is built.
-- (you should never change this except as a sanity check)
shouldAssetsAlwaysBeBuilt = false

-- The following is the list of assets to be built
assets =
{
	VertexShaders =
	{
		tool = "VertexShaderBuilder",
		extensions =
		{
			source = "hlsl",
			target = "vp",
		},
		names =
		{
			"example",
		},
		shouldAssetsAlwaysBeBuilt = false,
	},
	FragmentShaders =
	{
		tool = "FragmentShaderBuilder",
		extensions =
		{
			source = "hlsl",
			target = "fp",
		},
		names =
		{
			"example",
			"SpecularLight",
			"AlphaBinaryBlending",
			"PartialBlending",
		},
		shouldAssetsAlwaysBeBuilt = false,
	},
	Meshes =
	{
		tool = "MeshBuilder",
		extensions =
		{
			source = "txt",
			target = "bin",
		},
		names =
		{
			"snowMan",
			"sphere",
			"cylinder",
			"cone",
			"plane",
			"wall",
			"mesh1",
			"mesh2",
			"mesh3",
			"mesh4",
			"mesh5",
			"mesh6",
			"collisionMesh",
		},
		shouldAssetsAlwaysBeBuilt = false,
	},
	Textures =
	{
		tool = "TextureBuilder",
		extensions =
		{
			source = "png",
			target = "png",
		},
		names =
		{
			"example1",
			"example2",
			"fez",
			"mario",
			"megaman",
			"flower",
			"additiveEffect",
			"normalMap",
			 "stone",
			 "brick",
			
		},
		shouldAssetsAlwaysBeBuilt = false,
	},
	Effects=
	{
	  tool="EffectBuilder",
	   extensions=
	   {

	     source="txt",
		 target="txt",
	    },
		 names=
		 {
		    "effect1",
			"effect2",
			"effect3",
			"effect4",
			

		 },
		 shouldAssertsAlwaysBeBuilt =false,
    },

	Materials=
	{
	  tool="MaterialBuilder",
	  extensions=
	  {
	   
	    source="txt",
		target="txt",
	   },
	   names=
	   {
	     "materialFez",
		 "materialMario",
		 "materialMegaman",
		 "materialFlower",
		 "materialWizard",
		 "materialKarateka",
		 "materialNormalMap",
		},
	  shouldAssertsAlwaysBeBuilt=false,
	},

	Entities=
	{
	  tool="EntityBuilder",
	  extensions=
	  {
	     source="txt",
		 target="txt",
	  },
	  names=
	  {
	    "entity1",
		"entity2",
		"entity3",
		"entity4",
		"entity5",
		"entity6",
		"entity7",
		"entity8",
		"entity9",

	  },
	  shouldAssertsAlwaysBeBuilt=false,
	},

	Scenes=
	{
	  tool="SceneBuilder",
	  extensions=
	  {
	     source="txt",
		 target="txt",
	   },
	   names=
	   {
	     "scene1",
		 "scene2",
	   },
	   shouldAssersAlwaysBeBuilt=false,
	  },




	-- This is not a real asset;
	-- it is just an example of using Lua for a file format if you are interested or curious...
	-- Feel free to delete it or comment it out
	LuaFileFormatExamples =
	{
		tool = "ExampleLuaBuilder",
		extensions =
		{
			source = "lua",
			target = "lua",
		},
		names =
		{
			"example",
		},
		shouldAssetsAlwaysBeBuilt = false,
	}
}
