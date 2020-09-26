/**
 *  Copyright 2020 by André Schlinke <schlinke.andre@gmail.com>
 *  
 *  This file is part of brln.
 *  
 *  brln is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.

 *  brln is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU General Public License
 *  along with brln.  If not, see <https://www.gnu.org/licenses/>.
 */
#include "gtest/gtest.h"
#include "soundengine.h"

TEST(TestCaseSoundEnginge, TestSoundEngine) {
  auto soundEngine = SoundEngine::instance();
  auto status = soundEngine.init("./pd");
#ifdef CONTAINER_ENV
  ASSERT_EQ(EngineStatus::noSoundDevices, status);
#else
  ASSERT_EQ(EngineStatus::ready, status);
  for (int i = 0; i < 10; i++) {
      soundEngine.set("frequencyInput", i);
      soundEngine.update();
      ASSERT_EQ(i, soundEngine.get("frequencyInput"));
  }
#endif
}
