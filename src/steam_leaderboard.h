// Copyright (c) 2016 Greenheart Games Pty. Ltd. All rights reserved.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef SRC_STEAM_LEADERBOARD_H_
#define SRC_STEAM_LEADERBOARD_H_

#include <map>
#include <string>
#include "steam/steam_api.h"

namespace greenworks
{
  namespace leaderboard
  {
    // 排行榜句柄池
    extern std::map<std::string, SteamLeaderboard_t> leaderboardHandlePool;

    // 排行榜句柄同步查询器
    class LeaderBoardFinder
    {
    public:
      LeaderBoardFinder();
      SteamLeaderboard_t SyncFindLeaderBoard(std::string leaderBoardName);

    private:
      void onFindLeaderboard(LeaderboardFindResult_t *pResult, bool bIOFailure);

      CCallResult<LeaderBoardFinder, LeaderboardFindResult_t> m_callResultFindLeaderboard;
      SteamLeaderboard_t m_CurrentLeaderboard;

      bool b_complete;
    };
  }
} // namespace greenworks

#endif // SRC_STEAM_LEADERBOARD_H_
