# Pixel Streaming development workflow

Pixel Streaming is a deployment layer, not the primary day-to-day play-test loop.

## Local development

1. Use normal Play In Editor for fast Blueprint/map iteration.
2. Enable the Pixel Streaming plugin available in your installed Unreal version.
3. Test locally against the signaling server and open the local browser URL.
4. Package a Windows build and test that through Pixel Streaming before doing any AWS work.

The local machine can render and encode the stream, so cloud infrastructure is not required for solo development testing.

## Production direction

Browser -> Pixel Streaming frontend/signaling -> Unreal render instance -> Python Crown Circuit API/database.

Keep GPU/render infrastructure independent from the persistent league API so Pixel Streaming instances can be started and stopped without risking league state.
