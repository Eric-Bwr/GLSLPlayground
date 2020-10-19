vec2 map(vec2 x, vec2 in_min, vec2 in_max, vec2 out_min, vec2 out_max) {
    vec2 result;
    result.x = (x.x - in_min.x) * (out_max.x - out_min.x) / (in_max.x - in_min.x) + out_min.x;
    result.y = (x.y - in_min.y) * (out_max.y - out_min.y) / (in_max.y - in_min.y) + out_min.y;
    return result;
}

float roundCorners(float alpha, vec4 radii, vec2 position){
    float yMaxY = uiHeight - radii.y;
    float xMaxZ = uiWidth - radii.z;
    float yMaxZ = uiHeight - radii.z;
    float xMaxW = uiWidth - radii.w;
    if(position.x < radii.x && position.y < radii.x){
        alpha *= 1.0 - smoothstep(radii.x - smoothness, radii.x + smoothness, length(position - vec2(radii.x)));
    }else if(position.x < radii.y && position.y > yMaxY){
        alpha *= 1.0 - smoothstep(radii.y - smoothness, radii.y + smoothness, length(position - vec2(radii.y, yMaxY)));
    }else if(position.x > xMaxZ && position.y > yMaxZ){
        alpha *= 1.0 - smoothstep(radii.z - smoothness, radii.z + smoothness, length(position - vec2(xMaxZ, yMaxZ)));
    } else if(position.x > xMaxW && position.y < radii.w){
        alpha *= 1.0 - smoothstep(radii.w - smoothness, radii.w + smoothness, length(position - vec2(xMaxW, radii.w)));
    }
    return alpha;
}