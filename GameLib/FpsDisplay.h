/**
 * @file FpsDisplay.h
 * @author Jon Price
 */

#ifndef PROJECT1_FPSDISPLAY_H
#define PROJECT1_FPSDISPLAY_H

/**
 * Class to display fps
 */
class FpsDisplay {
private:
    double mFrames; ///< FPS
public:
    void Update(double elapsed);
    void Draw(std::shared_ptr<wxGraphicsContext> graphics);
};


#endif //PROJECT1_FPSDISPLAY_H