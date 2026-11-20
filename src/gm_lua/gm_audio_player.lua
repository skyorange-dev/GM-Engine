
Audio_Player={}

function Audio_Player.new()
    local chunk={}
    local music={}

    local function PlayMusic(music_name,loops)
         if loops ==nil then
            loops=0;
        end
        if music[music_name]==nil then
            music[music_name]=C_GetAudio(music_name,1);--音乐     
        end

        C_PlayMusic(music[music_name],loops);
    end

    local function PlayChunk(chunk_name,channel,loops,time)
        if channel ==nil then
            channel=-1;
        end
         if loops ==nil then
            loops=0;
        end

        if time==nil then
            time=-1;
        end

        if chunk[chunk_name]==nil then
             chunk[chunk_name]=C_GetAudio(music_name,0);--音效  
        end
        C_PlayChunk(channel,music[chunk_name],loops,time)
    end

    local function PauseMusic()
        C_PauseMusic();
       
    end

    local function PauseChunk(channel)
         C_PauseChunk(channel);
    end

    local function ResumeChunk(channel)
         C_ResumeChunk(channel);
    end

    local function ResumeMusic()
         C_ResumeMusic();
    end

    local function StopChunk(channel,ticks)
         if channel ==nil then
            channel=-1;
        end
         if ticks ==nil then
            ticks=0;
        end
        C_StopChunk(channel,ticsks);
    end

    local function StopMusic()
         C_StopMusic();
    end

    local function FadeInChunk(chunk_name,channel,loops,ms)
         if channel ==nil then
            channel=-1;
        end
         if loops ==nil then
            loops=0;
        end

        if  ms==nil then
            ms=1000;
        end
        if chunk[chunk_name]==nil then
             chunk[chunk_name]=C_GetAudio(music_name,0);--音效  
        end
        C_FadeInChunk(channel,chunk[chunk_name],loops,ms)
    end
   
    local function FadeInMusic(music_name,loops,ms,position)
         if loops ==nil then
            loops=0;
        end
         if ms ==nil then
            ms=1000;
        end
         if position ==nil then
            posituion=0;
        end
        if music[music_name]==nil then
            music[music_name]=C_GetAudio(music_name,1);--音乐     
        end
        C_FadeInMusic(music[music_name],loops,ms,position)
    end

     local function FadeOutChunk(channel,ms)
            if loops ==nil then
            channel=-1;
            end
        
         if ms ==nil then
            ms=1000;
        end
        C_FadeOutChunk(channel,ms)
    end
   
    local function FadeOutMusic(ms)
         if ms ==nil then
            ms=1000;
        end
        C_FadeOutMusic()
    end

    local function RewindMusic()
        C_RewindMusic();
    end

    local function VolumeChunk(channel,vloume)
        if channel == nil then
            channel=-1;
        end
        C_VolumeChunk(channel,vloume)
      
    end

    local function VolumeChunkData(chunk_name,volume)
        C_VolumeChunkData(chunk[chunk_name],volume)
    end
 
    local function ValumeMusic(vloume)
        C_VolumeMusic(vloume);
    end

    local function SetMusicPosition(time_position)
        C_SetMusicPosition(time_position);
    end

    local function SetChunkPanning(channel,left,right)
        C_SetChunkPanning(channel,left,right);
    end

    local function SetChannelDistance(channel,distance)
        C_SetChannelDistance(channel,distance)
    end

    local function SetChannelPosition(channel,angle,distance)
        C_SetChannelPosition(channel,angle,distance);
    end

    local function Delete()
        for k,v in pairs(chunk) do
            C_DeleteAudio(k);
            music[k]=nil;
        end

        for k,v in pairs(music) do
             C_DeleteAudio(k);
        end
    end

    return {
        PlayMusic=PlayMusic,
        PlayChunk=PlayChunk,
        PauseMusic=PauseMusic,
        PauseChunk=PauseChunk,
        ResumeChunk=ResumeChunk,
        ResumeMusic=ResumeMusic,
        StopChunk=StopChunk,
        StopMusic=StopMusic,
        FadeInChunk=FadeInChunk,
        FadeInMusic=FadeInMusic,
        FadeOutChunk=FadeOutChunk,
        FadeOutMusic=FadeOutMusic,
        RewindMusic=RewindMusic,
        VolumeChunk=VolumeChunk,
        VolumeChunkData=VolumeChunkData,
        ValumeMusic=ValumeMusic,
        SetMusicPosition=SetMusicPosition,
        SetChunkPanning=SetChunkPanning,
        SetChannelDistance=SetChannelDistance,
        SetChannelPosition=SetChannelPosition,
        Delete=Delete
    }
end
