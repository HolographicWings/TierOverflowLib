# TierOverflowLib

TierOverflowLib is a library mod for **Satisfactory** that extend the game by adding a scroller to the list of tiers. This allows modders to add new tiers beyond the default limit and unlock them via a method or a Blueprint node.

![Banner](https://raw.githubusercontent.com/HolographicWings/TierOverflowLib/refs/heads/main/Screenshots/WEBP/Banner.webp)

## Table of Contents

- [Features](#features)
- [Manual Installation](#manual-installation-not-recommended-use-satisfactory-mod-manager)
- [Usage](#usage-for-modders)
  - [Adding New Tiers](#adding-new-tiers)
  - [Unlocking Tiers](#unlocking-tiers)
- [API Reference](#api-reference)
  - [Methods](#methods)
  - [Blueprint Nodes](#blueprint-nodes)
- [Future Features](#future-features)
- [Support](#support)

## Features

- **Scrollable Tier List**: Adds a scroller to the tier list, allowing for an extended number of tiers.
- **Dynamic Tier Addition**: Enables adding new tiers beyond the default game limit.
- **Unlock Mechanisms**: Unlock new tiers using a method call or a Blueprint node.

![GameplayScreenshot2](https://raw.githubusercontent.com/HolographicWings/TierOverflowLib/refs/heads/main/Screenshots/WEBP/GameplayScreenshot2.webp)

## Manual Installation (Not recommended, use [Satisfactory Mod Manager](https://ficsit.app/))
1. Download the mod from the [mod page](https://ficsit.app/mod/TierOverflowLib).
2. Open the downloaded file as a zip with Winrar or 7-Zip:
3. Open the folder coresponding to your situation.
   - Windows or Linux client : `Windows`
   - Windows Dedicated Server : `WindowsServer` (Not tested on server)
   - Linux Dedicated Server : `LinuxServer` (Not tested on server)
4. Go in the install directory of the game (eg; C:\Program Files (x86)\Steam\steamapps\common\Satisfactory) then in it's mod folder (.\Satisfactory\FactoryGame\Mods) and create a new folder named "TierOverflowLib".
5. Drop the content of the folder you opened in the step 3, inside of this new TierOverflowLib folder.
6. Ensure you installed SML as well.
7. Launch the game.

## Usage (for modders)
First you need to clone this repository into the 'mods' folder of your modding UE project ('mods' is in the same folder as the .uproject file)
Then run the project with Unreal Engine, rebuild TierOverflowLib if the prompt which asking it appears.

### Adding New Tiers

To add a new tier to the game:

1. Simply create a new schematic in your mod and put it the TechTier int of your choice.
  ![SchematicTechTier](https://raw.githubusercontent.com/HolographicWings/TierOverflowLib/refs/heads/main/Screenshots/WEBP/SchematicTechTier.webp)
2. Add the schematic in your mod's GameWorldModule as on the modding docs.

### Unlocking Tiers

Unlock new tiers using one of the following methods:

- **Blueprint Node**: Use the `ApplyMaxTier` Blueprint node in your Unreal Engine Blueprints.
  ![ApplyMaxTierBlueprintNode](https://raw.githubusercontent.com/HolographicWings/TierOverflowLib/refs/heads/main/Screenshots/WEBP/ApplyMaxTierBlueprintNode.webp)
- **Method Call**: Use the `UTierOverflowLib_BPNodes::ApplyMaxTier` method in your mod's code, fill it with an instance of the session's Phase Manager and Schematic Manager, then with an int for the tier you wish to unlock.

## API Reference

### Methods

- `ApplyMaxTier(AFGGamePhaseManager* phaseManager, AFGSchematicManager* schematicManager, int32 maxTierNumber, bool force)`: Unlock the wished tier.

### Blueprint Nodes

- `ApplyMaxTier`: Unlock the wished tier.

- `ApplyPhase`: Apply a custom phase from a phase asset (can break the game progression).
- `ApplyPhaseSimple`: Apply a custom phase from a phase name and tier number (can break the game progression).
- `ApplyVanillaPhaseFromIndex`: Unlocks a vanilla phase from it's number.
- `ApplyNextVanillaPhase`: Unlocks the next vanilla phase.
- `UnlockAllVanillaPhases`: Unlocks all the vanilla phases.

![PhaseManagementBlueprintNodes](https://raw.githubusercontent.com/HolographicWings/TierOverflowLib/refs/heads/main/Screenshots/WEBP/PhaseManagementBlueprintNodes.webp)


## Future Features

- **Improved Ore Wheel**: Adding a similar pages system for the ressources scan wheel if there are too many ores.
- **Configurable Scroller**: Adding a setting to always show the scroller, even if there are no new tiers.
- **Server Compatibility Testing**: Ensure the mod works seamlessly in multiplayer environments.
- **Console & Chat Commands**: Introduce commands to interact with the mod features.
- **Milestone Integration**:
  - Allow to unlock a tier from a schematic.
  - Display the unlocked tiers graphically in the milestone rewards.

## Support

For support, questions, or suggestions:

- **GitHub Issues**: [Link to GitHub Issues](https://github.com/HolographicWings/TierOverflowLib/issues)
- **Discord**: Join the [Modding Discord](https://discord.gg/fPPqfY9j) and ping me from my username 'HolographicWings' (on the proper channels tho please)
