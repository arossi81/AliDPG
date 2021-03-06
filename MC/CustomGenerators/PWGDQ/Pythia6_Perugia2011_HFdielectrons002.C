AliGenerator *MbPythiaTunePerugia2011bcforcele(Int_t flag);
Float_t energy;

AliGenerator *
GeneratorCustom()
{
  Int_t flag = (Int_t)gRandom->Uniform(0,100);
  energy = energyConfig;
  return MbPythiaTunePerugia2011bcforcele(flag);
}

AliGenerator* MbPythiaTunePerugia2011bcforcele(Int_t flag)
{


  // load libraries to use Evtgen
  gSystem->Load("libPhotos");
  //gSystem->Load("libEvtGenBase");
  //gSystem->Load("libEvtGenModels");
  gSystem->Load("libEvtGen");
  gSystem->Load("libEvtGenExternal");
  gSystem->Load("libTEvtGen");  

  //TVirtualMCDecayer* decayer = new AliDecayerPythia();
  //decayer->SetForceDecay(kAll);
  //decayer->Init();
  //gMC->SetExternalDecayer(decayer);

  AliGenCocktail *gener = new AliGenCocktail();
  gener->UsePerEventRates();

  comment = comment.Append(" pp: Pythia MB (Perugia2011) + HF->ee or (B->)J/psi->ee in |y|<1.2");

  //    Pythia
  AliGenPythia* pythiaMB = GeneratorPythia6(kPythia6Tune_Perugia2011);

  ////////////////////////////////////////////
  //    Pythia cc->ee
  ////////////////////////////////////////////
  AliGenPythia* pythiaCC = new AliGenPythia(-1);
  pythiaCC->SetTitle("PYTHIA-HF-Cdiele");
  pythiaCC->SetMomentumRange(0, 999999.);
  pythiaCC->SetThetaRange(0., 180.);
  //pythia->SetYRange(-2.,2.);                                              
  pythiaCC->SetPtRange(0,1000.);
  pythiaCC->SetProcess(kPyCharmppMNRwmi);
  //pythia->SetProcess(kPyBeautyppMNR);
  pythiaCC->SetEnergyCMS(energy);
  pythiaCC->SetForceDecay(kSemiElectronic);
  //    Tune                                                                
  //    320     Perugia 0 
  //    350     Perugia 2011
  pythiaCC->SetTune(350);
  pythiaCC->UseNewMultipleInteractionsScenario();
  //
  //    decays 
  pythiaCC->SetCutOnChild(2);
  pythiaCC->SetPdgCodeParticleforAcceptanceCut(11);
  pythiaCC->SetChildYRange(-1.2,1.2);
  pythiaCC->SetChildPtRange(0,10000.);
  pythiaCC->SetStackFillOpt(AliGenPythia::kHeavyFlavor);

  ////////////////////////////////////////////
  //    Pythia bb->ee
  ////////////////////////////////////////////
  AliGenPythia* pythiaBB = new AliGenPythia(-1);
  pythiaBB->SetTitle("PYTHIA-HF-Bdiele");
  pythiaBB->SetMomentumRange(0, 999999.);
  pythiaBB->SetThetaRange(0., 180.);
  pythiaBB->SetPtRange(0,1000.);
  pythiaBB->SetProcess(kPyBeautyppMNRwmi);
  pythiaBB->SetEnergyCMS(energy);
  pythiaBB->SetForceDecay(kSemiElectronic);
  //    Tune                                                                
  //    320     Perugia 0 
  //    350     Perugia 2011
  pythiaBB->SetTune(350);
  pythiaBB->UseNewMultipleInteractionsScenario();
  //
  //    decays 
  pythiaBB->SetCutOnChild(2);
  pythiaBB->SetPdgCodeParticleforAcceptanceCut(11);
  pythiaBB->SetChildYRange(-1.2,1.2);
  pythiaBB->SetChildPtRange(0,10000.);
  pythiaBB->SetStackFillOpt(AliGenPythia::kHeavyFlavor);


  ////////////////////////////////////////////
  //    Pythia b,c->e
  ////////////////////////////////////////////
  AliGenPythia* pythiaB= new AliGenPythia(-1);
  pythiaB->SetTitle("PYTHIA-HF-Bele");
  pythiaB->SetMomentumRange(0, 999999.);
  pythiaB->SetThetaRange(0., 180.);
  pythiaB->SetPtRange(0,1000.);
  pythiaB->SetProcess(kPyBeautyppMNRwmi);
  pythiaB->SetEnergyCMS(energy);
  //pythiaB->SetForceDecay(kSemiElectronic);
  //    Tune                                                                
  //    320     Perugia 0 
  //    350     Perugia 2011
  pythiaB->SetTune(350);
  pythiaB->UseNewMultipleInteractionsScenario();
  //
  //    decays 
  pythiaB->SetCutOnChild(1);
  pythiaB->SetPdgCodeParticleforAcceptanceCut(11);
  pythiaB->SetChildYRange(-1.2,1.2);
  pythiaB->SetChildPtRange(0,10000.);
  pythiaB->SetStackFillOpt(AliGenPythia::kHeavyFlavor);
  
  gener->AddGenerator(pythiaMB,"Pythia MB",1.);
  
  if(flag>=0 && flag<10){ 
    gener->AddGenerator(pythiaCC,"Pythia CC",1.);
  }else if(flag>=10 && flag<20){ 
    gener->AddGenerator(pythiaBB,"Pythia BB",1.);
  }else if(flag>=20 && flag<100){ 
    gener->AddGenerator(pythiaB,"Pythia B",1.);
  }

  return gener;
}
