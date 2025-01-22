```sh
export LD_LIBRARY_PATH=/usr/local/lib:$LD_LIBRARY_PATH
```

```c
// Query example

Queries.it = ecs_query_iter(Game.world, Queries.position_sprite);
while (ecs_query_next(&Queries.it)) {
  Position *p = ecs_field(&Queries.it, Position, 0);
  Sprite *s = ecs_field(&Queries.it, Sprite, 1);
  for (int i = 0; i < Queries.it.count; i++) {
    DrawTexture(Assets.textures[s[i].idx], p[i].x - s[i].origin.x,
                p[i].y - s[i].origin.y, s[i].color);
    DrawRectangle(p[i].x, p[i].y, 1, 1, (Color){255, 0, 0, 255});
  }
}
```
