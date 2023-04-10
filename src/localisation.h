#pragma once
#include "game.h"

enum kLanguage{kEN, kDE, kES, kFR, kRU, kNLanguage};

void initLocalisation(void);

void resetLocalisation(const enum kLanguage _l);

void modLanguage(const bool _forward);

int16_t tY(void);

enum kLanguage getLanguage(void);

enum kTR{
  kTRBeltShort,
  kTRBeltLong,
  kTRSpltIShort,
  kTRSplitILong,
  kTRSplitLShort,
  kTRSplitLLong,
  kTRSplitTShort,
  kTRSplitTLong,
  kTRFilterIShort,
  kTRFilterILong,
  kTRFilterLShort,
  kTRFilterLLong,
  kTRTunnelShort,
  kTRTunnelLong,
  kTROverflowIShort,
  kTROverflowILong,
  kTROverflowLShort,
  kTROverflowLLong,
  kTRCarrotPWorld,
  kTRCarrotP,
  kTRSunflowerPWorld,
  kTRSunflowerP,
  kTRPotatoPWorld,
  kTRPotatoP,
  kTRApplePWorld,
  kTRAppleP,
  kTRCornPWorld,
  kTRCornP,
  kTRSeaweedPWorld,
  kTRSeaweedP,
  kTRWheetPWorld,
  kTRWheetP,
  kTRCactusPWorld,
  kTRCactusP,
  kTRLimePWorld,
  kTRLimeP,
  kTRStrawberryPWorld,
  kTRStrawberryP,
  kTRBambooPWorld,
  kTRBambooP,
  kTRCoffeePWorld,
  kTRCoffeeP,
  kTRCocoaPWorld,
  kTRCocoaP,
  kTRSeaCucumberPWorld,
  kTRSeaCucumberP,
  kTRRosePWorld,
  kTRRoseP,
  kTRPath,
  kTRSign,
  kTRBin,
  kTRWell,
  kTRStorageBox,
  kTRBufferBox,
  kTRFactoryUpgrade,
  kTRConveyorGrease,
  kTRObstructionRemover,
  kTRLandfill,
  kTRRotavator,
  kTRRetiremmentCottage,
  kTRFence,
  kTRHarvesterSmallShort,
  kTRHarvesterSmallLong,
  kTRPump,
  kTRChalkQuarry,
  kTRSaltMine,
  kTRHarvesterLargeShort,
  kTRHarvesterLargeLong,
  kTRCO2Extractor,
  kTRFacVitamin,
  kTRFacVegOil,
  kTRFacCrisps,
  kTRFacEthanol,
  kTRFacHardCider,
  kTRFacAbattoir,
  kTRFacHydrogen,
  kTRFacHOil,
  kTRFacCornDog,
  kTRFacBeer,
  kTRFacTequila,
  kTRFacHFCS,
  kTRFacGelatin,
  kTRFacJelly,
  kTRFacJelloShot,
  kTRFacEmulsifiers,
  kTRFacIceCream,
  kTRFacBatteryFarm,
  kTRFacProtein,
  kTRFacChocolate,
  kTRFacPie,
  kTRFacMSG,
  kTRFacTVDinner,
  kTRFacCake,
  kTRFacCaffeine,
  kTRFacEnergyDrink,
  kTRFacRaveJuice,
  kTRFacPerkPill,
  kTRFacPackaging,
  kTRFacDessert,
  kTRFacCateringKit,
  kTRFacChineseReadyMeal,
  kTRFacPartyPack,
  kTRFacParfume,
  kTRFacMiraclePowder,
  kTRFacTurkishDelight,
  kTRShop,
  kTRSales,
  kTRExports,
  kTRImports,
  kTRWarp,
  kTRSus,
  kTRCarrotPlural,
  kTRCarrot,
  kTRChalkPlural,
  kTRChalk,
  kTRVitaminPlural,
  kTRVitamin,
  kTRPotatoPlural,
  kTRPotato,
  kTRSunflowerPlural,
  kTRSunflower,
  kTROilPlural,
  kTROil,
  kTRSaltPlural,
  kTRSalt,
  kTRCrispsPlural,
  kTRCrisps,
  kTRApplePlural,
  kTRApple,
  kTRWaterBarrelPlural,
  kTRWaterBarrel,
  kTREthanolPlural,
  kTREthanol,
  kTRHardCiderPlural,
  kTRHardCider,
  kTRCornPlural,
  kTRCorn,
  kTRSeaweedPlural,
  kTRSeaweed,
  kTRMeatPlural,
  kTRMeat,
  kTRHydrogenPlural,
  kTRHydrogen,
  kTRHOilPlural,
  kTRHOil,
  kTRCornDogPlural,
  kTRCornDog,
  kTRWheatPlural,
  kTRWheat,
  kTRBeerPlural,
  kTRBeer,
  kTRCactusPlural,
  kTRCactus,
  kTRTequilaPlural,
  kTRTequila,
  kTRLimePlural,
  kTRLime,
  kTRHFCSPlural,
  kTRHFCS,
  kTRGelatinPlural,
  kTRGelatin,
  kTRJellyPlural,
  kTRJelly,
  kTRJelloShotPlural,
  kTRJelloShot,
  kTRStrawberryPlural,
  kTRStrawberry,
  kTREmulsifiersPlural,
  kTREmulsifiers,
  kTRIceCreamPlural,
  kTRIceCream,
  kTREggsPlural,
  kTREggs,
  kTRProteinPlural,
  kTRProtein,
  kTRCocoBeanPlural,
  kTRCocoBean,
  kTRChocolatePlural,
  kTRChocolate,
  kTRMeatPiePlural,
  kTRMeatPie,
  kTRMSGPlural,
  kTRMSG,
  kTRTVDinnerPlural,
  kTRTVDinner,
  kTRCakTRePlural,
  kTRCake,
  kTRCoffeeBeanPlural,
  kTRCoffeeBean,
  kTRCO2Plural,
  kTRCO2,
  kTRCaffeinePlural,
  kTRCaffeine,
  kTREnergyDrinkPlural,
  kTREnergyDrink,
  kTRRaveJuicePlural,
  kTRRaveJuice,
  kTRPerkPillsPlural,
  kTRPerkPills,
  kTRBambooPlural,
  kTRBamboo,
  kTRPackagingPlural,
  kTRPackaging,
  kTRDessertPlural,
  kTRDessert,
  kTRCateringKitPlural,
  kTRCateringKit,
  kTRFooYoungPlural,
  kTRFooYoung,
  kTRPartyPackPlural,
  kTRPartyPack,
  kTRSeaCucumberPlural,
  kTRSeaCucumber,
  kTRParfumePlural,
  kTRParfume,
  kTRMiraclePowderPlural,
  kTRMiraclePowder,
  kTRRosePlural,
  kTRRose,
  kTRTurkishDelightPlural,
  kTRTurkishDelight,
  kTRMainMenu,
  kTRDeleteSave1,
  kTRDeleteSave2,
  kTRDeleteSave3,
  kTRLoad,
  kTRSave,
  kTRMenu,
  kTRWater,
  kTRWet,
  kTRMoist,
  kTRDry,
  kTRSiltyGround,
  kTRChalkyGround,
  kTRPeatyGround,
  kTRSandyGround,
  kTRClayGround,
  kTRLoamyGround,
  kTRSoil,
  kTRPavedGround,
  kTRObstructedGround,
  kTRLake,
  kTRRiver,
  kTROcean,
  kTRSiltWorldMask,
  kTRSiltWorld,
  kTRChalkWorldMask,
  kTRChalkWorld,
  kTRPeatWorldMask,
  kTRPeatWorld,
  kTRSandWorldMask,
  kTRSandWorld,
  kTRClayWorldMask,
  kTRClayWorld,
  kTRLoamWoarldMask,
  kTRLoamWoarld,
  kTRWaterWorldMask,
  kTRWaterWorld,
  kTRTranquilWorldMask,
  kTRTranquilWorld,
  kTRPick,
  kTRInspect,
  kTRDestroy,
  kTRPickHelp,
  kTRInspectHelp,
  kTRDestroyHelp,
  kTRTopShop,
  kTRTopSales,
  kTRTopWarp,
  kTRTopExports,
  kTRTopImports,
  kTRTopCredits,
  kTRTutStage,
  kTRN,
  kTRE,
  kTRS,
  kTRW,
  kTRWE,
  kTRNS,
  kTRNE,
  kTRES,
  kTRSW,
  kTRWN,
  kTRWNE,
  kTRNES,
  kTRESW,
  kTRSWN,
  kTRObstructedGroundHelp1,
  kTRObstructedGroundHelp2,
  kTRPlaceMode,
  kTRPlantMode,
  kTRBuildMode,
  kTRPickupMode,
  kTRInventoryMode,
  kTRInspectMode,
  kTRDestroyMode,
  kTRNewCrop,
  kTRNewConveyor,
  kTRNewExtractor,
  kTRNewFactory,
  kTRNewUtility,
  kTRUICatToolPlural,
  kTRUICatTool,
  kTRUICatPlantPlural,
  kTRUICatPlant,
  kTRUICatConvPlural,
  kTRUICatConv,
  kTRUICatExtractorPlural,
  kTRUICatExtractor,
  kTRUICatFactoryPlural,
  kTRUICatFactory,
  kTRUICatUtilityPlural,
  kTRUICatUtility,
  kTRUICatCargoPlural,
  kTRUICatCargo,
  kTRUICatWarpPlural,
  kTRUICatWarp,
  kTRUICatImportNPlural,
  kTRUICatImportN,
  kTRUICatImportEPlural,
  kTRUICatImportE,
  kTRUICatImportSPlural,
  kTRUICatImportS,
  kTRUICatImportWPlural,
  kTRUICatImportW,
  kTRSaving,
  kTRGenerating,
  kTRLoading,
  kTRNewGame,
  kTRLoadDemo,
  kTRContinue,
  kTRTutDemo0,
  kTRTutDemo1,
  kTRTutDemo2,
  kTRTutDemo3,
  kTRTutDemo4,
  kTRTut0_0,
  kTRTut0_1,
  kTRTut0_2,
  kTRTut0_3,
  kTRTut0_4,
  kTRTut0_5,
  kTRTut0_6,
  kTRTut0_7,
  kTRTut0_8,
  kTRTut1_0,
  kTRTut1_1,
  kTRTut1_2,
  kTRTut1_3,
  kTRTut1_4,
  kTRTut1_5,
  kTRTut1_6,
  kTRTut1_7,
  kTRTut1_8,
  kTRTut2_0,
  kTRTut2_1,
  kTRTut2_2,
  kTRTut2_3,
  kTRTut2_4,
  kTRTut2_5,
  kTRTut2_6,
  kTRTut2_7,
  kTRTut2_8,
  kTRTut3_0,
  kTRTut3_1,
  kTRTut3_2,
  kTRTut3_3,
  kTRTut3_4,
  kTRTut3_5,
  kTRTut3_6,
  kTRTut3_7,
  kTRTut3_8,
  kTRTut4_0,
  kTRTut4_1,
  kTRTut4_2,
  kTRTut4_3,
  kTRTut4_4,
  kTRTut4_5,
  kTRTut4_6,
  kTRTut4_7,
  kTRTut4_8,
  kTRTut5_0,
  kTRTut5_1,
  kTRTut5_2,
  kTRTut5_3,
  kTRTut5_4,
  kTRTut5_5,
  kTRTut5_6,
  kTRTut5_7,
  kTRTut5_8,
  kTRTut6_0,
  kTRTut6_1,
  kTRTut6_2,
  kTRTut6_3,
  kTRTut6_4,
  kTRTut6_5,
  kTRTut6_6,
  kTRTut6_7,
  kTRTut6_8,
  kTRTut7_0,
  kTRTut7_1,
  kTRTut7_2,
  kTRTut7_3,
  kTRTut7_4,
  kTRTut7_5,
  kTRTut7_6,
  kTRTut7_7,
  kTRTut7_8,
  kTRTut8_0,
  kTRTut8_1,
  kTRTut8_2,
  kTRTut8_3,
  kTRTut8_4,
  kTRTut8_5,
  kTRTut8_6,
  kTRTut8_7,
  kTRTut8_8,
  kTRTut9_0,
  kTRTut9_1,
  kTRTut9_2,
  kTRTut9_3,
  kTRTut9_4,
  kTRTut10_0,
  kTRTut10_1,
  kTRTut10_2,
  kTRTut10_3,
  kTRTut10_4,
  kTRTut10_5,
  kTRTut10_6,
  kTRTut10_7,
  kTRTut10_8,
  kTRTut11_0,
  kTRTut11_1,
  kTRTut11_2,
  kTRTut11_3,
  kTRTut11_4,
  kTRTut11_5,
  kTRTut11_6,
  kTRTut11_7,
  kTRTut11_8,
  kTRTut12_0,
  kTRTut12_1,
  kTRTut12_2,
  kTRTut12_3,
  kTRTut12_4,
  kTRTut12_5,
  kTRTut12_6,
  kTRTut12_7,
  kTRTut12_8,
  kTRTut13_0,
  kTRTut13_1,
  kTRTut13_2,
  kTRTut13_3,
  kTRTut13_4,
  kTRConvTransitN,
  kTRConvTransitE,
  kTRConvTransitS,
  kTRConvTransitW,
  kTRConvSpeed,
  kTRConvNoFilter0,
  kTRConvNoFilter1,
  kTRConvFilter,
  kTRConvNextTransit,
  kTRExtractorHopper,
  kTROut,
  kTRFacFlavIngredients,
  kTRFacFlavGlycerin,
  kTRFacFlavBeta,
  kTRFacFlavCarotene ,
  kTRFacFlavSoy,
  kTRFacFlavLecithin,
  kTRFacFlavCalCarbonate0,
  kTRFacFlavCalCarbonate1,
  kTRFacFlavStabilizers,
  kTRFacFlavPreservatives,
  kTRFacFlavArtificialFlav0,
  kTRFacFlavArtificialFlav1,
  kTRFacFlavDistilled,
  kTRFacFlavVegetable,
  kTRFacFlavAlcohol,
  kTRFacFlavAppleJuice0,
  kTRFacFlavAppleJuice1,
  kTRFacFlavArtificialColoring0,
  kTRFacFlavArtificialColoring1,
  kTRFacFlavAnimalFeed,
  kTRFacFlavHormones,
  kTRFacFlavSteroids,
  kTRFacFlavProcess,
  kTRFacFlavElectrolysis0,
  kTRFacFlavElectrolysis1,
  kTRFacFlavElectrolysis2,
  kTRFacFlavSunset,
  kTRFacFlavOrange,
  kTRFacFlavHydrogenatedOil0,
  kTRFacFlavHydrogenatedOil1,
  kTRFacFlavHopOil0,
  kTRFacFlavHopOil1,
  kTRFacFlavAgave,
  kTRFacFlavHFCS0,
  kTRFacFlavHFCS1,
  kTRFacFlavHFCS2,
  kTRFacFlavHFCS3,
  kTRFacFlavAnticakingAgents0,
  kTRFacFlavAnticakingAgents1,
  kTRFacFlavAntibiotics,
  kTRFacFlavDewormer,
  kTRFacFlavInsecticides,
  kTRFacFlavGlutamicAcid,
  kTRFacFlavSodium,
  kTRFacFlavMSG0,
  kTRFacFlavMSG1,
  kTRFacFlavRequirements,
  kTRFacFlavSolvent,
  kTRFacFlavTitaniumDioxide0,
  kTRFacFlavTitaniumDioxide1,
  kTRFacFlavBleach,
  kTRFacFlavFruitSyrup0,
  kTRFacFlavFruitSyrup1,
  kTRFacFlavPack,
  kTRFacFlavBox,
  kTRFacFlavFormaldehyde,
  kTRFacFlavStarch,
  kTRFacProdTime,
  kTRFacTimeRemaining,
  kTRFacIn,
  kTRPlantLikes,
  kTRPlantHas,
  kTRPlantCannotGrow,
  kTRPlantGrowTime,
  kTRPlantHarvest,
  kTRPlantTimeLeft,
  kTRSpecialShop0,
  kTRSpecialShop1,
  kTRSpecialShop2,
  kTRSpecialShop3,
  kTRSpecialSales0,
  kTRSpecialSales1,
  kTRSpecialSales2,
  kTRSpecialSales3,
  kTRSpecialWarp0,
  kTRSpecialWarp1,
  kTRSpecialWarp2,
  kTRSpecialWarp3,
  kTRSpecialExport0,
  kTRSpecialExport1,
  kTRSpecialExport2,
  kTRSpecialExport3,
  kTRSpecialImport0,
  kTRSpecialImport1,
  kTRSpecialImport2,
  kTRSpecialImport3,
  kTRSpecialRock0,
  kTRSpecialRock1,
  kTRSpecialRock2,
  kTRSpecialRock3,
  kTRUtilityPath,
  kTRUtilityFence,
  kTRUtilityRetirement,
  kTRUtilitySign0,
  kTRUtilitySign1,
  kTRUtilityBin0,
  kTRUtilityBin1,
  kTRUtilityRotavator0,
  kTRUtilityRotavator1,
  kTRUtilityRotavator2,
  kTRUtilityFactoryUpgrade0,
  kTRUtilityFactoryUpgrade1,
  kTRUtilityFactoryUpgrade2,
  kTRUtilityFactoryUpgrade3,
  kTRUtilityFactoryUpgrade4,
  kTRUtilityFactoryUpgrade5,
  kTRUtilityWell,
  kTRUtilityStorage,
  kTRUIExportExporting,
  kTRUIExportThisPlot,
  kTRUIExportAllPlots,
  kTRUIImportOf,
  kTRUIImporters,
  kTRUIImported,
  kTRUIInventoryPlant,
  kTRUIInventoryPlace,
  kTRUIInventoryBuild,
  kTRInventory,
  kTRUIInventoryValue,
  kTRUIInventoryBuildOn,
  kTRUIInventoryBuildOnWater,
  kTRUIInventorySowOnWater,
  kTRUIInventoryPlaceInOcean,
  kTRUIInventoryCannotRemove,
  kTRUIInventoryBuildOnPlains,
  kTRNewBelt,
  kTRNewSplit2_180,
  kTRNewSplit2_90,
  kTRNewSplit3,
  kTRNewOverflow,
  kTRNewFilter,
  kTRNewTunnel,
  kTRNewCarrotPlant,
  kTRNewSunflowerPlant,
  kTRNewPotatoPlant,
  kTRNewAppleTree,
  kTRNewCornPlant,
  kTRNewSeaweedPlant,
  kTRNewWheatPlant,
  kTRNewCactusPlant,
  kTRNewLimeTree,
  kTRNewStrawberryPlant,
  kTRNewCocoaPlant,
  kTRNewCoffeePlant,
  kTRNewBambooPlant,
  kTRNewSeaCucumberPlant,
  kTRNewRosePlant,
  kTRNewPath,
  kTRNewSign,
  kTRNewBin,
  kTRNewWell,
  kTRNewStorageBox,
  kTRNewBuffferBox,
  kTRNewFactoryUpgrade,
  kTRNewConveyorGrease,
  kTRNewObstructionRemover,
  kTRNewLandfill,
  kTRNewRotavator,
  kTRNewRetirement,
  kTRNewFence,
  kTRNewCropHarvesterSmall,
  kTRNewPump,
  kTRNewChalkQuarry,
  kTRNewSaltMine,
  kTRNewCropHarvesterLarge,
  kTRNewCO2Extractor,
  kTRNewVitiminFac,
  kTRNewVegOilFac,
  kTRNewCrispsFac,
  kTRNewEthanolFac,
  kTRNewHardCiderFac,
  kTRNewAbattoir,
  kTRNewHydrogenFac,
  kTRNewHOILFac,
  kTRNewCornDogFac,
  kTRNewBeerFac,
  kTRNewTequilaFac,
  kTRNewHFCSFac,
  kTRNewGelatinFac,
  kTRNewJellyFac,
  kTRNewJelloShotFac,
  kTRNewEmulsifierFac,
  kTRNewIceCreamFac,
  kTRNewBatteryFarm,
  kTRNewProteinFac,
  kTRNewChocolateFac,
  kTRNewPieFac,
  kTRNewMSGFac,
  kTRNewTVDinnerFac,
  kTRNewCaffeineFac,
  kTRNewEnergyDrinkFac,
  kTRNewRaveJuiceFac,
  kTRNewPerkPillFac,
  kTRNewCakeFac,
  kTRNewDessertFac,
  kTRNewPackagingFac,
  kTRNewCateringKitFac,
  kTRNewChineseReayMealFac,
  kTRNewPartyPackFac,
  kTRNewParfumeFac,
  kTRNewMiraclePowderFac,
  kTRNewTurkishDelightFac,
  kTRSell,
  kTRPauseFin0,
  kTRPauseFin1,
  kTRPauseFin2,
  kTRPauseFin3,
  kTRPauseUnlock0,
  kTRPauseUnlock1,
  kTRPauseUnlock2,
  kTRPauseSell0,
  kTRPauseSell1,
  kTRPauseSell2,
  kTRPauseTut0,
  kTRPauseTut1,
  kTRPauseTut2,
  kTRPauseTut3,
  kTRPauseSave,
  kTRPauseTotTime,
  kTRPauseTotTimeDisplay,
  kTRSettingsAutosaveOff,
  kTRSettingsAutosave5m,
  kTRSettingsAutosave10m,
  kTRSettingsAutosave15m,
  kTRSettingsAutosave30m,
  kTRSettings0,
  kTRSettings1,
  kTRSettings2,
  kTRSettings3,
  kTRSettings4,
  kTRSettings5,
  kTRSettings6,
  kTRSettings7,
  kTRSettings8,
  kTRSettings9,
  kTRSettings10,
  kTRSettings11,
  kTRSettings12,
  kTRSettings13,
  kTRSettings14,
  kTRSettings15,
  kTRSettings16,
  kTRSettings17,
  kTRSettings18,
  kTRSettings19,
  kTRSettings20,
  kTRSettings21,
  kTRSettings22,
  kTRSettings23,
  kTRSettings24,
  kTRSettings25,
  kTRSettings26,
  kTRSettings27,
  kTRSettings28,
  kTRSettings29,
  kTRSettings30,
  kTRSettings31,
  kTRSettings32,
  kTRSettings33,
  kTRSettings34,
  kTRSettings35,
  kTRSettings36,
  kTRSettings37,
  kTRSettings38,
  kTRSettings39,
  kTRSettings40,
  kTRSettings41,
  kTRSettings42,
  kTRSettings43,
  kTRSettings44,
  kTRSettings45,
  kTRSettings46,
  kTRSettings47,
  kTRSettings48,
  kTRSettings49,
  kTRSettings50,
  kTRSettings51,
  kTRSettings52,
  kTRSettings53,
  kTRSettings54,
  kTRSettings55,
  kTRSettings56,
  kTRSettings57,
  kTRSettings58,
  kTRSettings59,
  kTRSettings60,
  kTRSettings61,
  kTRSettings62,
  kTRSettings63,
  kTRSettings64,
  kTRSettings65,
  kTRSettings66,
  kTRSettings67,
  kTRSettings68,
  kTRSettings69,
  kTRSettings70,
  kTRSettings71,
  kTRSettings72,
  kTRSettings73,
  kTRSettings74,
  kTRSettings75,
  kTRSettings76,
  kTRShopBuy,
  kTRShopPrice,
  kTRWarpLocations,
  kTRWarpSoil,
  kTRFactory,
  kTRFarming,
  kTRFactoryFarming,
  kTRLang,
  kNTR
};

const char* tr(const enum kTR _tr);

size_t trLen(const enum kTR _tr);