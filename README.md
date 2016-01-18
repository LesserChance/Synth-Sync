# Synth-Sync

The goal of Synth-Sync is to have a modular device that will allow me to control the BPM of synths in relation to one another.

The design is such that you can do things like double/half/quarter speed at any time signature, but also by chaining devices together allows you to play different time signatures at the same BPM on different synths.

Voltage sync is based specifically around the Korg Volca series of synths

## Modes
Synth-Sync can operate in two modes, master and slave. Mode will automatically be determined based on if a signal is being sent to the device.

**Master**: Set the BPM to be sent to children.  
  
**Slave**: Obtain BPM from parent. Alter BPM to children to be either:
- +X: X beats per parent BPM (i.e. output 5 beats per beat from parent)
- -X: X parent BPM per 1 beat (i.e. output 1 beat every 5 beats from parent)

## Example Setups
Device A (4/4 @120 BPM), Device B (4/4 @ 30 BPM)  
> **Master**: Output at 120 BPM  -> Slave, Device A  
> **Slave**: -4 (1 beat for every 4 of the parent) -> Device B  

Device A (4/4 @120 BPM), Device B (4/4 triplets @ 120 BPM)  
> **Master**: Output at 120 BPM  -> Slave, Device A  
> **Slave**: +3 (3 beats for every 1 of the parent) -> Device B  

Device A (4/4 @120 BPM), Device B (5/4 @ 120 BPM)  
> **Master**: Output at 120 BPM  -> Slave A, Device A  
> **Slave A**: -4 (1 beat for every 4 of the parent) -> Slave B  
> **Slave B**: +5 (5 beats for every 1 of the parent) -> Device B  

## Code
tbd

## Device Design
tbd

## Part List
tbd

## Schematics
tbd