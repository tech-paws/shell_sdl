#pragma once

#include <glm/glm.hpp>
#include "game_state.hpp"

// General
static const u64 GAPI_COMMAND_EXECUTE_MACRO = 0x0001;
static const u64 GAPI_COMMAND_BEGIN_MACRO = 0x0002;
static const u64 GAPI_COMMAND_END_MACRO = 0x0003;

// Pipelines
static const u64 GAPI_COMMAND_SET_COLOR_PIPELINE = 0x0101;
static const u64 GAPI_COMMAND_SET_TEXTURE_PIPELINE = 0x0102;

// Draw
static const u64 GAPI_COMMAND_DRAW_LINES = 0x0201;
static const u64 GAPI_COMMAND_DRAW_PATH = 0x0202;
static const u64 GAPI_COMMAND_DRAW_QUADS = 0x0203;
static const u64 GAPI_COMMAND_DRAW_CENTERED_QUADS = 0x0204;
static const u64 GAPI_COMMAND_DRAW_TEXTS = 0x0205;

struct GAPICommandPayload {
    u64 size;
    u8* base;
};

struct GAPICommand {
    u64 id;
    GAPICommandPayload payload;
};

static const GAPICommandPayload gapiEmptyCommandPayload = {0, nullptr};

inline void gapiPushCommand(GameState& gameState, u64 id, GAPICommandPayload payload) {
    GAPICommand command = { id, payload };
    auto result = regionMemoryPushStruct(&gameState.memory.gapiCommandsBuffer, command);
    resultUnwrap(result);
}

template<typename T>
GAPICommandPayload gapiCreateCommandPayload(GameState& gameState, T* values, size_t len) {
    auto dataResult = regionMemoryPushChunk(&gameState.memory.gapiCommandsDataBuffer, values, len);
    auto data = resultUnwrap(dataResult);
    return { len * sizeof(T), data };
}

// General

inline void gapiExecuteMacro(GameState& gameState, u64 id) {
    auto payload = gapiCreateCommandPayload(gameState, &id, 1);
    gapiPushCommand(gameState, GAPI_COMMAND_EXECUTE_MACRO, payload);
}

inline void gapiBeginMacro(GameState& gameState, u64 id) {
    auto payload = gapiCreateCommandPayload(gameState, &id, 1);
    gapiPushCommand(gameState, GAPI_COMMAND_BEGIN_MACRO, payload);
}

inline void gapiEndMacro(GameState& gameState, u64 id) {
    auto payload = gapiCreateCommandPayload(gameState, &id, 1);
    gapiPushCommand(gameState, GAPI_COMMAND_END_MACRO, payload);
}

// Pipelines

inline void gapiSetColorPipeline(GameState& gameState, glm::vec4 color) {
    auto payload = gapiCreateCommandPayload(gameState, &color, 1);
    gapiPushCommand(gameState, GAPI_COMMAND_SET_COLOR_PIPELINE, payload);
}

inline void gapiSetTexturePipeline(GameState& gameState, u64 textureId) {
    auto payload = gapiCreateCommandPayload(gameState, &textureId, 1);
    gapiPushCommand(gameState, GAPI_COMMAND_SET_TEXTURE_PIPELINE, payload);
}

// Draw

inline void drawLines(GameState& gameState, glm::vec3* points, size_t count) {
    auto payload = gapiCreateCommandPayload(gameState, points, count);
    gapiPushCommand(gameState, GAPI_COMMAND_DRAW_LINES, payload);
}

inline void drawPath(GameState& gameState, glm::vec3* points, size_t count) {
    auto payload = gapiCreateCommandPayload(gameState, points, count);
    gapiPushCommand(gameState, GAPI_COMMAND_DRAW_PATH, payload);
}

inline void drawQuads(GameState& gameState, glm::mat4* quadsMvpMatrices, size_t count) {
    auto payload = gapiCreateCommandPayload(gameState, quadsMvpMatrices, count);
    gapiPushCommand(gameState, GAPI_COMMAND_DRAW_QUADS, payload);
}

inline void drawCenteredQuads(GameState& gameState, glm::mat4* quadsMvpMatrices, size_t count) {
    auto payload = gapiCreateCommandPayload(gameState, quadsMvpMatrices, count);
    gapiPushCommand(gameState, GAPI_COMMAND_DRAW_CENTERED_QUADS, payload);
}

inline void drawTexts(GameState& gameState, String* texts, size_t count) {
    auto payload = gapiCreateCommandPayload(gameState, texts, count);
    gapiPushCommand(gameState, GAPI_COMMAND_DRAW_TEXTS, payload);
}
