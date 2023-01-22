// Copyright (c) 2017 Greenheart Games Pty. Ltd. All rights reserved.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "nan.h"
#include "v8.h"

#include "steam/steam_api.h"
#include "steam_api_registry.h"
#include "steam_async_worker.h"

namespace greenworks {
namespace api {
namespace {

NAN_METHOD(DownloadLeaderboardAll) {
  Nan::HandleScope scope;

  if (info.Length() < 2 || !info[0]->IsString() || !info[1]->IsFunction())
  {
    THROW_BAD_ARGS("Bad arguments");
  }
  std::string leaderboardName = (*(Nan::Utf8String(info[0])));
  Nan::Callback *success_callback =
      new Nan::Callback(info[1].As<v8::Function>());
  Nan::Callback *error_callback = nullptr;

  if (info.Length() > 2 && info[2]->IsFunction())
    error_callback = new Nan::Callback(info[2].As<v8::Function>());

  Nan::AsyncQueueWorker(new greenworks::LeaderBoardAllDownloadWorker(
      leaderboardName, success_callback, error_callback));
  info.GetReturnValue().Set(Nan::Undefined());
}

NAN_METHOD(UploadLeaderboardScore) {
  Nan::HandleScope scope;

  if (info.Length() < 4 || !info[0]->IsString() || !info[1]->IsInt32() ||
      !info[2]->IsInt32() || !info[3]->IsFunction())
  {
    THROW_BAD_ARGS("Bad arguments");
  }
  std::string leaderboardName = (*(Nan::Utf8String(info[0])));
  int score = Nan::To<int>(info[1]).FromJust();
  ELeaderboardUploadScoreMethod method =
      static_cast<ELeaderboardUploadScoreMethod>(Nan::To<int32>(info[2]).FromJust());
  Nan::Callback *success_callback =
      new Nan::Callback(info[3].As<v8::Function>());
  Nan::Callback *error_callback = nullptr;

  if (info.Length() > 4 && info[4]->IsFunction())
    error_callback = new Nan::Callback(info[4].As<v8::Function>());

  Nan::AsyncQueueWorker(new greenworks::LeaderBoardUploadScoreWorker(
      leaderboardName, score, method, success_callback, error_callback));
  info.GetReturnValue().Set(Nan::Undefined());
}

void RegisterAPIs(v8::Local<v8::Object> target) {
  SET_FUNCTION("downloadLeaderboardAll", DownloadLeaderboardAll);
  SET_FUNCTION("uploadLeaderboardScore", UploadLeaderboardScore);
}

SteamAPIRegistry::Add X(RegisterAPIs);

}  // namespace
}  // namespace api
}  // namespace greenworks
