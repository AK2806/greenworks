// Copyright (c) 2016 Greenheart Games Pty. Ltd. All rights reserved.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "steam_leaderboard.h"

#include "nan.h"
#include "greenworks_utils.h"

namespace greenworks
{
    namespace leaderboard
    {
        // 排行榜句柄池
        std::map<std::string, SteamLeaderboard_t> leaderboardHandlePool = std::map<std::string, SteamLeaderboard_t>();

        LeaderBoardFinder::LeaderBoardFinder() : m_CurrentLeaderboard(NULL), b_complete(false)
        {
        }

        SteamLeaderboard_t LeaderBoardFinder::SyncFindLeaderBoard(std::string leaderBoardName)
        {
            m_CurrentLeaderboard = NULL;

            SteamAPICall_t hSteamAPICall = SteamUserStats()->FindLeaderboard(leaderBoardName.c_str());
            m_callResultFindLeaderboard.Set(hSteamAPICall, this, &LeaderBoardFinder::onFindLeaderboard);

            while (!b_complete)
            {
                // sleep 100ms.
                utils::sleep(100);
            }

            return m_CurrentLeaderboard;
        }

        void LeaderBoardFinder::onFindLeaderboard(LeaderboardFindResult_t *pResult, bool bIOFailure)
        {
            // 检查调用期间是否遇到错误
            if (bIOFailure)
            {
                m_CurrentLeaderboard = NULL;
            }
            else if (pResult->m_bLeaderboardFound)
            {
                m_CurrentLeaderboard = pResult->m_hSteamLeaderboard;
            }
            else
            {
                m_CurrentLeaderboard = NULL;
            }

            b_complete = true;
        }
    }
} // namespace greenworks
