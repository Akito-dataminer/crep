/*****************************************************************
 * Copyright(c) 2023 Akito Dataminer
 *
 * This software is released under the MIT License.
 * Refer the accompanying LICENSE.txt or the description
 * at the provided URL for details.
 * http://opensource.org/licenses/mit-license.php
 ******************************************************************/

#pragma once

#include <string>

namespace crep::message {

constexpr const char *usage = R"(  Please specify as below:
    crep <project_name> <template_name>
)";

constexpr const char *help = R"(  crep is an abbreviation for "CREate Project".
  Usage is below:
    crep <project_name> <template_name>

  Upon executing this command, a directory named <project_name> is created
  in the current directory, and the specified template is copied into it.
  The template must be created in the location described below:
    <crep_config_directory>/template/

  The location of <crep_config_directory> varies by platform as follows:
    Windows: C:\Users\<user_name>\AppData\crep
    Linux: /home/<user_name>/.config/crep/template

  If you find it cumbersome to create templates, you can use the templates uploaded to
    https://github.com/Akito-dataminer/template
  by the creator of this tool. In that case, you'll need to copy the
  templates into the aforementioned directory using methods like git clone.
)";

}  // namespace crep::message
