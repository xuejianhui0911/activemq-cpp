/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _ACTIVEMQ_CONNECTOR_STOMP_COMMANDS_STOMPMESSAGE_H_
#define _ACTIVEMQ_CONNECTOR_STOMP_COMMANDS_STOMPMESSAGE_H_

#include <activemq/core/ActiveMQMessage.h>
#include <activemq/core/ActiveMQAckHandler.h>
#include <activemq/connector/stomp/commands/AbstractCommand.h>
#include <activemq/transport/Command.h>
#include <activemq/connector/stomp/StompTopic.h>
#include <activemq/exceptions/IllegalArgumentException.h>
#include <activemq/exceptions/NoSuchElementException.h>
#include <activemq/exceptions/RuntimeException.h>

#include <activemq/util/Date.h>
#include <activemq/util/Long.h>
#include <activemq/util/Integer.h>
#include <activemq/util/Boolean.h>

#include <string>
#include <sstream>

namespace activemq{
namespace connector{
namespace stomp{
namespace commands{

    /**
     * Base class for Stomp Commands that represent the Active MQ message
     * types.  This class is templated and expects the Template type to be
     * a cms::Message type, Message, TextMessage etc.  This class will
     * implement all the general cms:Message methods
     *
     * This class implement AbsractCommand<StompCommnd> and the
     * ActiveMQMessage interface.
     */
    template<typename T>
    class StompMessage :
        public AbstractCommand< transport::Command >,
        public T,
        public core::ActiveMQMessage
    {
    private:

        // Core API defined Acknowedge Handler.
        core::ActiveMQAckHandler* ackHandler;

        // Cached Destination
        cms::Destination* dest;

        // Cached Destination
        cms::Destination* replyTo;

    public:

        StompMessage() :
            AbstractCommand< transport::Command >(),
            ackHandler( NULL ),
            dest( NULL ),
            replyTo( NULL) {
        }

        StompMessage( StompFrame* frame ) :
            AbstractCommand< transport::Command >( frame ),
            ackHandler( NULL ),
            dest( NULL ),
            replyTo( NULL )
        {
            const std::string& destHeader = CommandConstants::toString(
                CommandConstants::HEADER_DESTINATION );
            const std::string& replyToHeader = CommandConstants::toString(
                CommandConstants::HEADER_REPLYTO );

            dest = CommandConstants::toDestination(
                getPropertyValue( destHeader, "" ) );

            std::string replyToValue = getPropertyValue( replyToHeader, "null" );
            if( replyToValue != "null" ) {
                replyTo = CommandConstants::toDestination( replyToValue );
            }
        }

    	virtual ~StompMessage() {

            if( dest != NULL ){
                delete dest;
            }

            if( replyTo != NULL ){
                delete replyTo;
            }
        }

        /**
         * Clears out the body of the message.  This does not clear the
         * headers or properties.
         */
        virtual void clearBody(){
            getFrame().getBody().clear();
        }

        /**
         * Clears the message properties.  Does not clear the body or
         * header values.
         */
        virtual void clearProperties(){

            util::Properties& props = getFrame().getProperties();
            std::vector< std::pair< std::string, std::string > > propArray = props.toArray();
            for( unsigned int ix=0; ix<propArray.size(); ++ix ){

                const std::string& name = propArray[ix].first;

                // Only clear properties that aren't Stomp headers.
                if( !CommandConstants::isStompHeader(name) ){
                    props.remove( name );
                }
            }
        }

        /**
         * Retrieves the propery names.
         * @return The complete set of property names currently in this
         * message.
         */
        virtual std::vector<std::string> getPropertyNames() const{
            std::vector<std::string> names;

            const util::Properties& props = getFrame().getProperties();
            std::vector< std::pair< std::string, std::string > > propArray = props.toArray();
            for( unsigned int ix=0; ix<propArray.size(); ++ix ){

                const std::string& name = propArray[ix].first;

                // Only clear properties that aren't Stomp headers.
                if( !CommandConstants::isStompHeader(name) ){
                    names.push_back( name );
                }
            }

            return names;
        }

        /**
         * Indicates whether or not a given property exists.
         * @param name The name of the property to look up.
         * @return True if the property exists in this message.
         */
        virtual bool propertyExists( const std::string& name ) const{
            if( CommandConstants::isStompHeader( name ) ){
                return false;
            }

            return getFrame().getProperties().hasProperty( name );
        }

        virtual bool getBooleanProperty( const std::string& name ) const
            throw( cms::CMSException ){
            std::string value = getStrictPropertyValue<std::string>( name );
            return value == "true";
        }

        virtual unsigned char getByteProperty( const std::string& name ) const
            throw( cms::CMSException ){
            return getStrictPropertyValue<unsigned char>(name);
        }

        virtual double getDoubleProperty( const std::string& name ) const
            throw( cms::CMSException ){
            return getStrictPropertyValue<double>(name);
        }

        virtual float getFloatProperty( const std::string& name ) const
            throw( cms::CMSException ){
            return getStrictPropertyValue<float>(name);
        }

        virtual int getIntProperty( const std::string& name ) const
            throw( cms::CMSException ){
            return getStrictPropertyValue<int>(name);
        }

        virtual long long getLongProperty( const std::string& name ) const
            throw( cms::CMSException ){
            return getStrictPropertyValue<long long>(name);
        }

        virtual short getShortProperty( const std::string& name ) const
            throw( cms::CMSException ){
            return getStrictPropertyValue<short>(name);
        }

        virtual std::string getStringProperty( const std::string& name ) const
            throw( cms::CMSException ){
            return getStrictPropertyValue<std::string>(name);
        }

        virtual void setBooleanProperty( const std::string& name,
            bool value ) throw( cms::CMSException ){
            testProperty( name );

            std::string strvalue = value? "true" : "false";
            setPropertyValue( name, strvalue );
        }

        virtual void setByteProperty( const std::string& name,
            unsigned char value ) throw( cms::CMSException ){
            setStrictPropertyValue<unsigned char>( name, value );
        }

        virtual void setDoubleProperty( const std::string& name,
            double value ) throw( cms::CMSException ){
            setStrictPropertyValue<double>( name, value );
        }

        virtual void setFloatProperty( const std::string& name,
            float value ) throw( cms::CMSException ){
            setStrictPropertyValue<float>( name, value );
        }

        virtual void setIntProperty( const std::string& name,
            int value ) throw( cms::CMSException ){
            setStrictPropertyValue<int>( name, value );
        }

        virtual void setLongProperty( const std::string& name,
            long long value ) throw( cms::CMSException ){
            setStrictPropertyValue<long long>( name, value );
        }

        virtual void setShortProperty( const std::string& name,
            short value ) throw( cms::CMSException ){
            setStrictPropertyValue<short>( name, value );
        }

        virtual void setStringProperty( const std::string& name,
            const std::string& value ) throw( cms::CMSException ){
            testProperty( name );
            setPropertyValue( name, value );
        }

        /**
         * Get the Correlation Id for this message
         * @return string representation of the correlation Id
         */
        virtual std::string getCMSCorrelationId() const {
            std::string correlationId = getPropertyValue(
                CommandConstants::toString(
                    CommandConstants::HEADER_CORRELATIONID ), "null" );
            if( correlationId == "null" ){
                return "";
            }
            return correlationId;
        }

        /**
         * Sets the Correlation Id used by this message
         * @param correlationId String representing the correlation id.
         */
        virtual void setCMSCorrelationId(const std::string& correlationId) {
            setPropertyValue(
                CommandConstants::toString(
                    CommandConstants::HEADER_CORRELATIONID ) ,
                correlationId );
        }

        /**
         * Acknowledges all consumed messages of the session
         * of this consumed message.
         * @throws CMSException
         */
        virtual void acknowledge() const throw( cms::CMSException ) {
            if(ackHandler != NULL) ackHandler->acknowledgeMessage( this );
        }

        /**
         * Sets the DeliveryMode for this message
         * @return DeliveryMode enumerated value.
         */
        virtual int getCMSDeliveryMode() const {
            if(!getFrame().getProperties().hasProperty(
                   CommandConstants::toString(
                       CommandConstants::HEADER_PERSISTENT ) ) ) {
                return cms::DeliveryMode::PERSISTENT;
            }

            if( util::Boolean::parseBoolean( getPropertyValue(
                       CommandConstants::toString(
                           CommandConstants::HEADER_PERSISTENT ) ) ) == true ) {
                return (int)cms::DeliveryMode::PERSISTENT;
            }

            return cms::DeliveryMode::NON_PERSISTENT;
        }

        /**
         * Sets the DeliveryMode for this message
         * @param mode DeliveryMode enumerated value.
         */
        virtual void setCMSDeliveryMode( int mode ) {
            std::string persistant = "true";

            if( mode == (int)cms::DeliveryMode::NON_PERSISTENT ) {
                persistant = "false";
            }

            setPropertyValue(
                CommandConstants::toString(
                    CommandConstants::HEADER_PERSISTENT ) ,
                persistant );
        }

        /**
         * Gets the Destination for this Message
         * @return Destination object can be NULL
         */
        virtual const cms::Destination* getCMSDestination() const{
            return dest;
        }

        /**
         * Sets the Destination for this message
         * @param destination Destination Object
         */
        virtual void setCMSDestination( const cms::Destination* destination ) {
            if( destination != NULL )
            {
                delete dest;
                dest = destination->clone();
                setPropertyValue(
                    CommandConstants::toString(
                        CommandConstants::HEADER_DESTINATION ),
                    dest->toProviderString() );
            }
        }

        /**
         * Gets the Expiration Time for this Message
         * @return time value
         */
        virtual long long getCMSExpiration() const {
            return util::Long::parseLong( getPropertyValue(
                CommandConstants::toString(
                    CommandConstants::HEADER_EXPIRES ), "0" ) );
        }

        /**
         * Sets the Expiration Time for this message
         * @param expireTime time value
         */
        virtual void setCMSExpiration( long long expireTime ) {
            setPropertyValue(
                CommandConstants::toString(
                    CommandConstants::HEADER_EXPIRES) ,
                util::Long::toString( expireTime ) );
        }

        /**
         * Gets the CMS Message Id for this Message
         * @return time value
         */
        virtual std::string getCMSMessageId() const {
            return getPropertyValue(
                CommandConstants::toString(
                    CommandConstants::HEADER_MESSAGEID ), "" );
        }

        /**
         * Sets the CMS Message Id for this message
         * @param id time value
         */
        virtual void setCMSMessageId( const std::string& id ) {
            setPropertyValue(
                CommandConstants::toString(
                    CommandConstants::HEADER_MESSAGEID ),
                id );
        }

        /**
         * Gets the Priority Value for this Message
         * @return priority value
         */
        virtual int getCMSPriority() const {
            return util::Integer::parseInt( getPropertyValue(
                CommandConstants::toString(
                    CommandConstants::HEADER_JMSPRIORITY ), "0" ) );
        }

        /**
         * Sets the Priority Value for this message
         * @param priority priority value
         */
        virtual void setCMSPriority( int priority ) {
            setPropertyValue(
                CommandConstants::toString(
                    CommandConstants::HEADER_JMSPRIORITY),
                util::Integer::toString( priority ) );
        }

        /**
         * Gets the Redelivered Flag for this Message
         * @return redelivered value
         */
        virtual bool getCMSRedelivered() const {
            return util::Boolean::parseBoolean( getPropertyValue(
                CommandConstants::toString(
                    CommandConstants::HEADER_REDELIVERED ),
                "false" ) );
        }

        /**
         * Sets the Redelivered Flag for this message
         * @param redelivered redelivered value
         */
        virtual void setCMSRedelivered( bool redelivered ) {
            setPropertyValue(
                CommandConstants::toString(
                    CommandConstants::HEADER_REDELIVERED ),
                util::Boolean::toString( redelivered ) );
        }

        /**
         * Gets the CMS Reply To Address for this Message
         * @return Reply To Value
         */
        virtual const cms::Destination* getCMSReplyTo() const {
            return replyTo;
        }

        /**
         * Sets the CMS Reply To Address for this message
         * @param id Reply To value
         */
        virtual void setCMSReplyTo( const cms::Destination* destination ) {
            if( destination != NULL )
            {
                delete replyTo;
                replyTo = destination->clone();
                setPropertyValue(
                    CommandConstants::toString(
                        CommandConstants::HEADER_REPLYTO ),
                    replyTo->toProviderString() );
            }
        }

        /**
         * Gets the Time Stamp for this Message
         * @return time stamp value
         */
        virtual long long getCMSTimeStamp() const {
            return util::Long::parseLong( getPropertyValue(
                CommandConstants::toString(
                    CommandConstants::HEADER_TIMESTAMP ), "0" ) );
        }

        /**
         * Sets the Time Stamp for this message
         * @param timeStamp time stamp value
         */
        virtual void setCMSTimeStamp( long long timeStamp ) {
            setPropertyValue(
                CommandConstants::toString(
                    CommandConstants::HEADER_TIMESTAMP ),
                util::Long::toString( timeStamp ) );
        }

        /**
         * Gets the CMS Message Type for this Message
         * @return type value
         */
        virtual std::string getCMSMessageType() const {
            std::string type = getPropertyValue(
                CommandConstants::toString(
                    CommandConstants::HEADER_TYPE ), "null" );
            if( type == "null" ){
                return "";
            }
            return type;
        }

        /**
         * Sets the CMS Message Type for this message
         * @param type type value
         */
        virtual void setCMSMessageType( const std::string& type ) {
            setPropertyValue(
                CommandConstants::toString(
                    CommandConstants::HEADER_TYPE ),
                type );
        }

    public:    // ActiveMQMessage

        /**
         * Sets the Acknowledgement Handler that this Message will use
         * when the Acknowledge method is called.
         * @param handler ActiveMQAckHandler
         */
        virtual void setAckHandler( core::ActiveMQAckHandler* handler ) {
            this->ackHandler = handler;
        }

        /**
         * Gets the number of times this message has been redelivered.
         * @return redelivery count
         */
        virtual int getRedeliveryCount() const {
            return util::Integer::parseInt( getPropertyValue(
                CommandConstants::toString(
                    CommandConstants::HEADER_REDELIVERYCOUNT ),
                "0" ) );
        }

        /**
         * Sets the count of the number of times this message has been
         * redelivered
         * @param count redelivery count
         */
        virtual void setRedeliveryCount( int count ) {
            setPropertyValue(
                CommandConstants::toString(
                    CommandConstants::HEADER_REDELIVERYCOUNT ),
                util::Integer::toString( count ) );
        }

        /**
         * Returns if this message has expired, meaning that its
         * Expiration time has elapsed.
         * @returns true if message is expired.
         */
        virtual bool isExpired() const {
            long long expireTime = this->getCMSExpiration();
            long long currentTime = util::Date::getCurrentTimeMilliseconds();
            if( expireTime > 0 && currentTime > expireTime ) {
                return true;
            }
            return false;
        }

    protected:

        /**
         * Checks to see if the given property has the name of a
         * pre-defined header.  If so, throws an exception.
         */
        virtual void testProperty( const std::string& name ) const
            throw( cms::CMSException ){
            if( CommandConstants::isStompHeader( name ) ){
                throw exceptions::IllegalArgumentException( __FILE__, __LINE__,
                    "searching for property with name of pre-defined header" );
            }
        }

        /**
         * Attempts to get a property from the frame's property
         * map.
         */
        template <typename TYPE>
        TYPE getStrictPropertyValue( const std::string& name ) const
            throw( cms::CMSException ){

            testProperty( name );

            if( !getProperties().hasProperty( name ) ){
                throw exceptions::NoSuchElementException( 
                    __FILE__, __LINE__,
                    "property not available in message" );
            }

            const char* strProp = getPropertyValue( name );
            std::istringstream stream( strProp );
            TYPE value;
            stream >> value;

            if( stream.fail() ){
                throw exceptions::RuntimeException( 
                    __FILE__, __LINE__,
                    "Error extracting property from string" );
            }

            return value;
        }

        /**
         * Attempts to set the property in the frame.  If an error occurs or
         * the property name is that of a pre-defined header, an exception
         * is thrown.
         */
        template <typename TYPE>
        void setStrictPropertyValue( const std::string& name, TYPE value )
            throw( cms::CMSException ){
            testProperty( name );

            std::ostringstream stream;
            stream << value;

            setPropertyValue( name, stream.str() );
        }

        /**
         * Inheritors are required to override this method to init the
         * frame with data appropriate for the command type.
         * @param frame Frame to init
         */
        virtual void initialize( StompFrame& frame )
        {
            frame.setCommand( CommandConstants::toString(
                CommandConstants::SEND ) );
        }

        /**
         * Inheritors are required to override this method to validate
         * the passed stomp frame before it is marshalled or unmarshaled
         * @param frame Frame to validate
         * @returns true if frame is valid
         */
        virtual bool validate( const StompFrame& frame ) const
        {
            if(frame.getCommand() ==
               CommandConstants::toString( CommandConstants::SEND ) )
            {
                if(frame.getProperties().hasProperty(
                    CommandConstants::toString(
                        CommandConstants::HEADER_DESTINATION ) ) )
                {
                    return true;
                }
            }
            else if( frame.getCommand() ==
                     CommandConstants::toString( CommandConstants::MESSAGE ) )
            {
                if(frame.getProperties().hasProperty(
                    CommandConstants::toString(
                        CommandConstants::HEADER_DESTINATION ) ) &&
                   frame.getProperties().hasProperty(
                    CommandConstants::toString(
                        CommandConstants::HEADER_MESSAGEID ) ) )
                {
                    return true;
                }
            }

            return false;
        }

    };

}}}}

#endif /*_ACTIVEMQ_CONNECTOR_STOMP_COMMANDS_STOMPMESSAGE_H_*/
