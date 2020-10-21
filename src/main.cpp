/*
 * The tool for the emotion analysis created for Andrea Esposito's Bachelor's Thesis.
 * Copyright (C) 2020 Andrea Esposito <a.esposito39@studenti.uniba.it>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/*! \mainpage Emotion Analysis Tool
 *
 * \tableofcontents
 *
 * \section the-tool The tool
 *
 * This tool is responsible of the emotion analysis of images. It can be used
 * through command line using its interface.
 *
 * ```
 * emotions [<option>...] IMAGE...
 *
 * <option> := -h | --help
 * ```
 *
 * Using the above CLI (Command Line Interface), the argument IMAGE can be used
 * multiple times. It must represents either a file containing _only_ the \ref
 * data_uri "data URI" of an image or the \ref data_uri "data URI" itself.
 *
 * \section the-project The project
 */

/**
 * \file main.cpp
 *
 * \brief The main file.
 *
 * This file is the main file of the tool.
 *
 * \author Andrea Esposito <[github.com/espositoandrea](https://github.com/espositoandrea)>
 */
#include <iostream>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv/cv.hpp>

#include <PhotoDetector.h>
#include <Frame.h>

#include "common/PlottingImageListener.hpp"
#include "common/StatusListener.hpp"

#include "exit_codes.hpp"
#include "utilities.hpp"
#include "base64.hpp"

/**
 * \brief The main entry point.
 *
 * This is the entry point of the tool.
 *
 * \param argc The length of `argv`.
 * \param argv The array of arguments given through the command line.
 * \return An \ref exit_codes "exit code" based on the execution.
 */
int main(int argc, char **argv)
{
    std::vector <std::string> images;
    const exit_codes result = setup_options(argc, argv, images);
    if (result != exit_codes::OK) return static_cast<int>(result);

    const unsigned int nFaces = 1;
    const int faceDetectorMode = (int) affdex::FaceDetectorMode::LARGE_FACES;

    std::shared_ptr <affdex::Detector> detector = std::make_shared<affdex::PhotoDetector>(nFaces,
                                                                                          (affdex::FaceDetectorMode) faceDetectorMode);

    std::shared_ptr <PlottingImageListener> listenPtr(new PlottingImageListener());

    detector->setDetectAllEmotions(true);
    detector->setDetectAllExpressions(true);
    detector->setDetectAllEmojis(true);
    detector->setDetectAllAppearances(true);
    detector->setClassifierPath(affdex::path("lib/affdex-sdk/data/"));
    detector->setImageListener(listenPtr.get());

    detector->start();

    std::shared_ptr <StatusListener> videoListenPtr = std::make_shared<StatusListener>();
    detector->setProcessStatusListener(videoListenPtr.get());

    for (const auto &image : images)
    {
        std::string decoded = base64::decode(image);
        cv::Mat img = cv::imdecode(std::vector<uchar>(decoded.begin(), decoded.end()), cv::IMREAD_UNCHANGED);

        affdex::Frame frame(img.size().width, img.size().height, img.data, affdex::Frame::COLOR_FORMAT::BGR);

        ((affdex::PhotoDetector *) detector.get())->process(frame); //Process an image

        do
        {
            if (listenPtr->getDataSize() > 0)
            {
                std::pair <Frame, std::map<FaceId, Face>> dataPoint = listenPtr->getData();
                affdex::Frame frame = dataPoint.first;
                std::map <FaceId, Face> faces = dataPoint.second;

                listenPtr->addResult(faces, frame.getTimestamp());
            }
        } while ((videoListenPtr->isRunning() || listenPtr->getDataSize() > 0));
    }

    listenPtr->outputToFile(std::cout);
    return 0;
}
