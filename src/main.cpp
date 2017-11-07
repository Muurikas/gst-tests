#include <gst/gst.h>
#include <unistd.h>

GstElement* videoSource;

GstElement* tee;

GstElement* jpegenc;
GstElement* rtpPay;

GstElement* autoVideosink;
GstElement* udpSink;

GstElement* pipeline;

int main(int argc, char** argv) {

    gst_init(&argc,  &argv);

    videoSource = gst_element_factory_make("videotestsrc","videosource");
    udpSink = gst_element_factory_make("udpsink", "videosink");
    g_object_set(udpSink,"host","127.0.0.1", NULL);
    g_object_set(udpSink, "port", 5000, NULL);
    tee = gst_element_factory_make("tee", "tee-element");

    jpegenc = gst_element_factory_make("jpegenc", "jpeg-element");
    rtpPay = gst_element_factory_make("rtpjpegpay", "rtp-element");

    pipeline = gst_pipeline_new("base-pipeline");
    gst_bin_add_many(GST_BIN(pipeline),videoSource, jpegenc, tee, rtpPay, udpSink, NULL);

    gst_element_link_many(videoSource, jpegenc, tee, rtpPay, udpSink, NULL);

    gst_element_set_state(pipeline, GST_STATE_PLAYING);
    g_warning("Pipeline 1st start");
    usleep(3000000);
    gst_element_set_state(pipeline, GST_STATE_NULL);
    gst_element_unlink(tee,udpSink);
    usleep(200000);
    gst_element_link(tee,udpSink);
    gst_element_set_state(pipeline,GST_STATE_PLAYING);
    g_warning("Pipeline 2nd start");


    while(1);

}
