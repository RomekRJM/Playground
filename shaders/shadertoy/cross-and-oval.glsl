void drawCircle( in vec2 uv, inout vec3 col ) {
    vec2 circle = vec2(.5+.2*sin(iTime), .5+.2*cos(iTime));
    float r = clamp(.1*abs(sin(iTime)), .0, .1);
    
    if (length(uv - circle) <= r) {
        col = vec3(.5 + sin(iTime), 1.0 - cos(iTime), 1.0 - sin(iTime));
    }
}

void drawCross( in vec2 uv, inout vec3 col ) {
    float threshold = clamp(0.2*abs(sin(iTime)), 0.05, 0.25);
    
    if (length(uv.x - uv.y) < threshold || length(uv.x - ( 1.0 - uv.y ) ) < threshold) {
        col = vec3(1.0);
    }
}


void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
    // Normalized pixel coordinates (from 0 to 1)
    vec2 uv = fragCoord/iResolution.xy;
    
    vec3 col = vec3(0.9*uv.xyx);
    
    drawCross(uv, col);
    drawCircle(uv, col);
    
    // Output to screen
    fragColor = vec4(col, 1.0);
}

