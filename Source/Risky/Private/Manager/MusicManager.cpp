// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/MusicManager.h"
#include "Components/AudioComponent.h"

void AMusicManager::BeginPlay()
{
	Super::BeginPlay();
	StartMusicLoop();
}

void AMusicManager::StartMusicLoop()
{
    if (MusicTracks.Num() == 0)
        return;

    // Create the audio component if it doesn't exist
    if (!MusicComponent)
    {
        MusicComponent = NewObject<UAudioComponent>(this);
        MusicComponent->RegisterComponent();
        MusicComponent->OnAudioFinished.AddDynamic(this, &AMusicManager::OnMusicFinished);
    }

    PlayRandomTrack();
}

void AMusicManager::PlayRandomTrack()
{
    if (MusicTracks.Num() == 0)
        return;

    int32 index = FMath::RandRange(0, MusicTracks.Num() - 1);
    USoundBase* track = MusicTracks[index];
    if (track && MusicComponent)
    {
        MusicComponent->SetSound(track);
        MusicComponent->Play();
    }
}


void AMusicManager::OnMusicFinished()
{
    PlayRandomTrack();
}