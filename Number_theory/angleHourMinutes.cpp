/* LC#1344

Given two numbers, hour and minutes, 
return the smaller angle (in degrees) 
formed between the hour and the minute hand.

Answers within 10^-5 
of the actual value will be accepted as correct.
*/

// beats ~100% LC users
double angleClock(int hour, int minutes) {
    double minutes_angle = 360 / 60 * minutes;
    double hour_angle = 360 / 12 * hour + (double)minutes / 2;
    if (hour_angle == minutes_angle)
        return 0;
    else if (hour_angle > minutes_angle && hour_angle - minutes_angle <= 180)
        return hour_angle - minutes_angle;
    else if (hour_angle > minutes_angle && hour_angle - minutes_angle > 180)
        return 360 - (hour_angle - minutes_angle);
    else if (hour_angle < minutes_angle && minutes_angle - hour_angle <= 180)
        return minutes_angle - hour_angle;
    else if (hour_angle < minutes_angle && minutes_angle - hour_angle > 180)
        return 360 - (minutes_angle - hour_angle);
    return 0;
}