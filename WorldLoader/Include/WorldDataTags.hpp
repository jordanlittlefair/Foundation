#pragma once

#ifndef _WORLDLOADER_WORLDDATATAGS_HPP_
#define _WORLDLOADER_WORLDDATATAGS_HPP_

/*
	Define the tags which make up the entities in an xml world file.
*/

#define WORLD_TAG		"World"
#define ASSETS_TAG		"Assets"
#define ENTITIES_TAG	"Entities"
#define ENTITY_TAG		"Entity"
#define NAME_TAG			"Name"
#define COMPONENTS_TAG	"Components"
#define NODES_TAG		"Nodes"

/*

<!-- An example of the structure of an xml world file -->

<World>
	<Entity>
		<Name>
			"The entity's name"
		<Name/>
		<Components>
			<!-- 
				A list of
				components
				stored in
				the entity.
			-->
		<Components/>
		<Nodes>
			<!--
				A list of
				nodes stored
				in the entity.
			-->
		<Nodes/>
	<Entity/>
	
	<!--
		More entities
		....
	-->
<World/>
			

*/

#endif