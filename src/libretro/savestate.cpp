#include "savestate.h"

#include <cstring>

const char* SaveState::stateTag = "NDSR";
const uint32_t SaveState::stateVersion = 3;

bool SaveState::check(const void* data, size_t& size)
{
  if (size == 0) return false;

  // Check if the format tag matches
  uint8_t tag[4];
  memcpy(tag, data, 4);

  for (int i = 0; i < 4; i++)
    if (tag[i] != stateTag[i])
      return false;

  // Check if the state version matches
  uint32_t version;
  memcpy(&version, (uint8_t*)data + 4, 4);

  if (version != stateVersion)
    return false;

  return true;
}

bool SaveState::save(void* data, size_t& size)
{
  // Open the state file and write the header
  MemFile file;

  file.write(stateTag, sizeof(uint8_t), 4);
  file.write(&stateVersion, sizeof(uint32_t), 1);

  // Save the state of every component
  core->memory.saveState(file);
  core->cartridgeGba.saveState(file);
  core->cartridgeNds.saveState(file);
  core->cp15.saveState(file);
  core->divSqrt.saveState(file);
  core->dma[0].saveState(file);
  core->dma[1].saveState(file);
  core->gpu.saveState(file);
  core->gpu2D[0].saveState(file);
  core->gpu2D[1].saveState(file);
  core->gpu3D.saveState(file);
  core->gpu3DRenderer.saveState(file);
  core->hleArm7.saveState(file);
  core->hleBios[0].saveState(file);
  core->hleBios[1].saveState(file);
  core->hleBios[2].saveState(file);
  core->interpreter[0].saveState(file);
  core->interpreter[1].saveState(file);
  core->ipc.saveState(file);
  core->rtc.saveState(file);
  core->spi.saveState(file);
  core->spu.saveState(file);
  core->timers[0].saveState(file);
  core->timers[1].saveState(file);
  core->wifi.saveState(file);
  core->saveState(file);

  // Write save data to buffer
  file.read(data, size, 1);

  return true;
}

bool SaveState::load(const void* data, size_t& size)
{
  // Open the state file and read past the header
  MemFile file;

  file.write(data, size, 1);
  file.seek(8, SEEK_SET);

  // Load the state of every component
  core->memory.loadState(file);
  core->cartridgeGba.loadState(file);
  core->cartridgeNds.loadState(file);
  core->cp15.loadState(file);
  core->divSqrt.loadState(file);
  core->dma[0].loadState(file);
  core->dma[1].loadState(file);
  core->gpu.loadState(file);
  core->gpu2D[0].loadState(file);
  core->gpu2D[1].loadState(file);
  core->gpu3D.loadState(file);
  core->gpu3DRenderer.loadState(file);
  core->hleArm7.loadState(file);
  core->hleBios[0].loadState(file);
  core->hleBios[1].loadState(file);
  core->hleBios[2].loadState(file);
  core->interpreter[0].loadState(file);
  core->interpreter[1].loadState(file);
  core->ipc.loadState(file);
  core->rtc.loadState(file);
  core->spi.loadState(file);
  core->spu.loadState(file);
  core->timers[0].loadState(file);
  core->timers[1].loadState(file);
  core->wifi.loadState(file);
  core->loadState(file);

  return true;
}
