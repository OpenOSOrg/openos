## Dockerfile for constructing the base Open Education Effort (OPE)
## container.  This container contains everything required for authoring OPE courses
## Well is should anyway ;-)

ARG FROM_REG
ARG FROM_IMAGE
ARG FROM_TAG

FROM ${FROM_REG}${FROM_IMAGE}${FROM_TAG}

LABEL maintainer="Open Education <opeffort@gmail.com>"

# ARGS are consumed and reset after FROM
# so any arguments you want to use below must be stated below FROM

ARG ADDITIONAL_DISTRO_PACKAGES
ARG PYTHON_PREREQ_VERSIONS
ARG PYTHON_INSTALL_PACKAGES

# Fix: https://github.com/hadolint/hadolint/wiki/DL4006
# Fix: https://github.com/koalaman/shellcheck/wiki/SC3014
SHELL ["/bin/bash", "-o", "pipefail", "-c"]

# Add a "USER root" statement followed by RUN statements to install system packages using apt-get,
# change file permissions, etc.

# install linux packages that we require for pdf authoring
USER root

RUN dpkg --add-architecture i386 && \
    apt-get -y update --fix-missing && \
    apt-get -y install ${ADDITIONAL_DISTRO_PACKAGES} && \
    apt-get clean && rm -rf /var/lib/apt/lists/*

# Now that distro packages are installed lets install the python packages we want
# This was inspired by
# https://github.com/jupyter/docker-stacks/blob/b186ce5fea6aa9af23fb74167dca52908cb28d71/scipy-notebook/Dockerfile

USER ${NB_UID}

# sometimes there are problems with the existing version of installed python packages
# these need to be installed to the prerequisite versions before we can install the rest of the
# packages. Install Python 3 packages
#RUN python --version

RUN conda install --quiet --yes conda=23.3.1 python=3.9.16 --no-pin --force-reinstall && \ 
    conda install --quiet --yes ${PYTHON_PREREQ_VERSIONS} && \
    conda install --quiet --yes ${PYTHON_INSTALL_PACKAGES} && \
    pip install nbclient==0.5.13 && \
    pip install jupyterlab_rise && \
    fix-permissions "${CONDA_DIR}" && \
    fix-permissions "/home/${NB_USER}" && \
    mamba clean -afy

USER ${NB_UID}

# Import matplotlib the first time to build the font cache.
ENV XDG_CACHE_HOME="/home/${NB_USER}/.cache/"

# copy overrides.json
COPY settings ${CONDA_DIR}/share/jupyter/lab/settings

USER root

# final bits of cleanup
RUN touch /home/${NB_USER}/.hushlogin && \
# use a short prompt to improve default behaviour in presentations
    echo "export PS1='\$ '" >> /home/${NB_USER}/.bashrc && \
# work around bug when term is xterm and emacs runs in xterm.js -- causes escape characters in file
    echo "export TERM=linux" >> /home/${NB_USER}/.bashrc && \
# finally remove default working directory from joyvan home
    rmdir /home/${NB_USER}/work && \
    # as per the nbstripout readme we setup nbstripout be always be used for the joyvan user for all repos
    nbstripout --install --system 

# Static Customize for OPE USER ID choices
# To avoid problems with start.sh logic we do not modify user name
# FIXME: Add support for swinging home directory if you want to point to a mounted volume
ARG DEFAULT_NB_UID=${NB_UID}
ARG OPE_UID
ARG OPE_GID
ARG OPE_GROUP
ARG CHOWN_HOME=yes
ARG CHOWN_HOME_OPTS="-R"
ARG CHOWN_EXTRA_OPTS='-R'
ARG CHOWN_EXTRA="${CONDA_DIR}"
ENV OPE_UID=${OPE_UID}
ENV NB_UID=${OPE_UID}
ENV OPE_GID=${OPE_GID}
ARG NB_GID=${OPE_GID}
ENV NB_GID=${NB_GID}
ENV OPE_GROUP=${OPE_GROUP}
ARG NB_GROUP=${OPE_GROUP}
ENV NB_GROUP=${NB_GROUP}

# Done customization

# jupyter-stack contains logic to run custom start hook scripts from
# two locations -- /usr/local/bin/start-notebook.d and
#                 /usr/local/bin/before-notebook.d
# and scripts in these directoreis are run automatically
# an opportunity to set things up based on dynamic facts such as user name

RUN /usr/local/bin/start.sh true; \
    echo "hardcoding $NB_USER to uid=$NB_UID and group name $NB_GROUP with gid=$NB_GID shell to /bin/bash" ; \
    usermod -s /bin/bash $NB_USER ; \
    [[ -w /etc/passwd ]] && echo "Removing write access to /etc/passwd" && chmod go-w /etc/passwd

COPY start-notebook.d /usr/local/bin/start-notebook.d

ENV USER=$NB_USER

# Change the ownership of the home directory to ope group so it starts up properly
RUN chgrp ${OPE_GROUP} -R /home

USER $NB_USER
CMD  ["/bin/bash", "-c", "cd /home/jovyan ; start-notebook.sh"]

