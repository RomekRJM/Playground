const float spread = .0111;
const int stars = 30;
const float speed = 0.05;

vec3 drawStars( in vec2 uv, in int cntr ) {
    
    float fcntr = float(cntr);
    float x = .5 + spread*fcntr*sin(speed*fcntr*iTime);
    float y = .5 + spread*fcntr*cos(speed*fcntr*iTime);
    
    if (cntr %2 == 0) {
        float helper = x;
        x = y;
        y = helper;
    }
    
    vec2 circle = vec2(x, y);
    float len = length(circle - uv);
    vec3 col = vec3(0.0);
    
    if (len > 0.0) {
        col = vec3(.5, .6, 1.0);
        col /= 20.0*len;
    }
    
    return col;
}

void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
    // Normalized pixel coordinates (from 0 to 1)
    vec2 uv = fragCoord/iResolution.xy;
    vec3 color = vec3(0.0);
    
    for(int cntr=1; cntr<=stars; cntr++) {
    	color += drawStars(uv, cntr);
    }
    color /= float(stars);
    
    // Output to screen
    fragColor = vec4(color, 1.0);
}

